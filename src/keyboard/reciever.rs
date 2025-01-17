use serde::{Deserialize, Serialize};
use std::sync::atomic::{AtomicBool, Ordering};
use std::sync::{Arc, Once};
use std::time::{SystemTime, UNIX_EPOCH};
use windows::Win32::UI::WindowsAndMessaging::{WH_KEYBOARD_LL, WM_KEYDOWN, WM_KEYUP};
use windows::Win32::{
    Foundation::{HINSTANCE, LPARAM, LRESULT, WPARAM},
    UI::WindowsAndMessaging::{
        DispatchMessageA, GetMessageA, SetWindowsHookExA, TranslateMessage, UnhookWindowsHookEx,
        HHOOK, MSG,
    },
};

pub type KeyboardProc = unsafe extern "system" fn(i32, WPARAM, LPARAM) -> LRESULT;

pub fn listen(callback: KeyboardProc, running: Arc<AtomicBool>) {
    static INIT: Once = Once::new();
    static mut HHOOK: Option<HHOOK> = None;

    unsafe {
        INIT.call_once(|| {
            let h_hook = SetWindowsHookExA(
                WH_KEYBOARD_LL,
                Some(callback),
                Some(HINSTANCE::default()),
                0,
            )
            .expect("Failed to install hook");

            HHOOK = Some(h_hook);
        });

        let mut msg = MSG::default();
        while GetMessageA(&mut msg, None, 0, 0).into() {
            // Don't know why I can't do anything in this loop.
            let _ = TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }

        println!("Exiting loop");
        running.store(false, Ordering::Relaxed);

        if let Some(h_hook) = HHOOK {
            UnhookWindowsHookEx(h_hook).unwrap();
        }
    }
}

#[derive(Debug, Deserialize, Serialize)]
pub enum KeyAction {
    Up,
    Down,
}

impl TryFrom<WPARAM> for KeyAction {
    type Error = String;

    fn try_from(value: WPARAM) -> Result<Self, Self::Error> {
        if value.0 == WM_KEYDOWN as usize {
            return Ok(Self::Down);
        } else if value.0 == WM_KEYUP as usize {
            return Ok(Self::Up);
        } else {
            return Err(format!("WPARAM {:#?} is neither Up or Down", value));
        }
    }
}

#[derive(Debug, Deserialize, Serialize)]
pub struct Record {
    pub timestamp: u64,
    pub key: u16,
    pub action: KeyAction,
}

impl Record {
    pub fn new(key: u16, action: KeyAction) -> Self {
        let Ok(n) = SystemTime::now().duration_since(UNIX_EPOCH) else {
            unreachable!();
        };

        Self {
            timestamp: n.as_secs(),
            key,
            action,
        }
    }
}
