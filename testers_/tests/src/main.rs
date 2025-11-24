use std::io::{self, Write};
use std::net::TcpStream;
use std::thread;
use std::time::Duration;

fn main() -> io::Result<()> {
    let address = format!("{}:{}", "127.0.0.1", 8080);
    let mut stream = TcpStream::connect(&address)?;
    stream.write_all(format!("{}", "type:{con};").as_bytes())?;
    Ok(())
}
