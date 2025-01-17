
use windows::Win32::
    UI::Input::KeyboardAndMouse::{
        keybd_event, MapVirtualKeyW, KEYEVENTF_KEYUP, KEYEVENTF_SCANCODE, MAPVK_VK_TO_VSC
    }
;

use super::{reciever::KeyAction, Record};

// fn char_to_vkey(c: u16) -> Result<u16, String> {
//     let result = unsafe { VkKeyScanW(c.into()) };

//     if result == -1 {
//         return Err(format!("No virtual key found for '{}'", c));
//     }

//     Ok((result & 0xFF) as u16)
// }

pub fn send_key(c: &Record) -> Result<(), String> {
    if c.key == 0 {
        return Err(format!("Invalid vkey {}", c.key));
    }

    let key_code = match c.action {
        KeyAction::Up => KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP,
        KeyAction::Down => KEYEVENTF_SCANCODE,
    };

    unsafe {
        let scancode = MapVirtualKeyW(c.key as u32, MAPVK_VK_TO_VSC);
        keybd_event(c.key.try_into().unwrap(), scancode.try_into().unwrap(), key_code, 0);
    }

    Ok(())
}
