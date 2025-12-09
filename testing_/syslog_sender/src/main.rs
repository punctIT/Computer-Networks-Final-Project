use std::io::{self, Write};
use std::net::TcpStream;
use std::thread;
use std::time::Duration;

fn main() -> io::Result<()> {
    let address = format!("{}:{}", "10.100.0.32", 1514);
    let mut stream = TcpStream::connect(&address)?;

    let logs = std::fs::read_to_string("logs.txt")?;
    for log in logs.lines() {
        println!("{}", log);
        
        stream.write_all(format!("{}\n", log).as_bytes())?;
        thread::sleep(Duration::from_secs(2)); 
    }

    Ok(())
}
