mod reciever;
mod sender;

use std::{
    sync::{
        atomic::{AtomicBool, Ordering},
        mpsc, Arc, Mutex, OnceLock,
    }, thread
};

use reciever::KeyAction;
pub use sender::send_key;

pub use reciever::Record;
use windows::Win32::{
    Foundation::{LPARAM, LRESULT, WPARAM},
    UI::{
        Input::KeyboardAndMouse::VK_END,
        WindowsAndMessaging::{CallNextHookEx, PostQuitMessage, WM_KEYDOWN, WM_KEYUP},
    },
};


static RESULT_SENDER: OnceLock<Arc<Mutex<mpsc::Sender<(WPARAM, u16)>>>> = OnceLock::new();

unsafe fn send_on_global_channel(x: (WPARAM, u16)) {
    
    if let Some(sender) = RESULT_SENDER.get() {
        if let Ok(s) = sender.lock() {
            if let Err(err) = s.send(x) {
                eprintln!("Failed to send key code: {}", err);
            }
        } else {
            eprintln!("Failed to acquire lock on sender");
        }
    }
}

// Example callback
unsafe extern "system" fn callback(n_code: i32, w_param: WPARAM, l_param: LPARAM) -> LRESULT {
    if n_code >= 0 {
        if w_param.0 == WM_KEYDOWN as usize || w_param.0 == WM_KEYUP as usize {
            let key_code = *(l_param.0 as *const u16);
            // println!("Key code: {}", key_code);

            // Example: Exit on F12 key press
            if key_code == VK_END.0 {
                println!("End pressed, exiting...");
                PostQuitMessage(0);
                return LRESULT(0);
            }

            send_on_global_channel((w_param, key_code));
        }
    }

    CallNextHookEx(None, n_code, w_param, l_param)
}

/// Record is a blocking call for
pub fn record() -> Vec<Record> {
    let (tx, rx) = mpsc::channel();
    RESULT_SENDER.get_or_init(|| Arc::new(Mutex::new(tx)));

    let running = Arc::new(AtomicBool::new(true));
    let running_clone = Arc::clone(&running);

    let listener_thread = thread::spawn(move || {
        reciever::listen(callback, running_clone);
    });

    let mut buffer: Vec<Record> = vec![];

    // Main thread loop
    println!("Main thread is working. Press END to quit...");
    while running.load(Ordering::Relaxed) {
        if let Ok(message) = rx.try_recv() {
            println!("Received key code: ({:#?}, {})", message.0 .0, message.1);
            let action = match KeyAction::try_from(message.0) {
                Ok(t) => t,
                Err(s) => panic!("{s}"),
            };

            buffer.push(Record::new(message.1, action));
            if message.1 == VK_END.0 {
                running.store(false, Ordering::Relaxed);
            }
        }
    }

    // Join the thread to ensure cleanup
    if let Err(err) = listener_thread.join() {
        eprintln!("Error joining listener thread: {:?}", err);
    }

    buffer
}
