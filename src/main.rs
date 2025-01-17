use std::{fs, io::BufReader, path::PathBuf, thread, time::Duration};

use clap::{Parser, Subcommand};
use keyboard::Record;
mod keyboard;

#[derive(Parser)]
#[command(version, about, long_about = None)]
struct Args {
    #[command(subcommand)]
    command: Option<Commands>,
}

#[derive(Subcommand)]
enum Commands {
    Record {
        #[arg(short, long, value_name = "FILE")]
        out: PathBuf,
        #[arg(short, long)]
        wait: Option<String>,
    },
    Play {
        #[arg(short, long, value_name = "FILE")]
        input: PathBuf,

        #[arg(short, long)]
        wait: Option<String>,
    },
}

fn main() {
    let cli = Args::parse();

    match &cli.command {
        Some(Commands::Record { out, wait }) => {
            if let Some(wait_time) = wait {
                let wait_for: Duration = wait_time.parse::<humantime::Duration>().unwrap().into();
                let sleep_for = wait_for.as_secs();
                if sleep_for > 0 {
                    for i in 0..sleep_for {
                        println!("Waiting for {}s", sleep_for - i);
                        thread::sleep(Duration::from_secs(1));
                    }
                } else {
                    println!("Waiting for {}s...", wait_for.as_secs());
                    thread::sleep(wait_for);
                }
                println!("Recording started!")
            }

            let keys = keyboard::record();
            let data = serde_json::to_string(&keys).unwrap();
            fs::write(out, data).unwrap();
        }
        Some(Commands::Play { input, wait }) => {
            let file = fs::File::open(input).unwrap();
            let reader = BufReader::new(file);
            let keys: Vec<Record> = serde_json::from_reader(reader).unwrap();

            println!("read from file");
            if let Some(wait_time) = wait {
                let wait_for: Duration = wait_time.parse::<humantime::Duration>().unwrap().into();
                let sleep_for = wait_for.as_secs();
                if sleep_for > 0 {
                    for i in 0..sleep_for {
                        println!("Waiting for {}s", sleep_for - i);
                        thread::sleep(Duration::from_secs(1));
                    }
                } else {
                    println!("Waiting for {}s...", wait_for.as_secs());
                    thread::sleep(wait_for);
                }
                println!("Replay started!")
            }

            println!("about to print");

            let mut delay: u64 = 0;

            for (i, key) in keys.iter().enumerate() {
                let gap = key.timestamp - delay;
                if i > 0 {
                    thread::sleep(Duration::from_secs(gap));
                }
                println!("Sending key: {:#?}", key);

                keyboard::send_key(key).unwrap();
                delay = key.timestamp;
            }
        }
        None => todo!(),
    }
}
