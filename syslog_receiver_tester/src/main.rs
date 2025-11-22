use std::io::{self, Write};
use std::net::TcpStream;

fn main() -> io::Result<()> {
    let address = format!("{}:{}", "127.0.0.1", 1514);
    let mut stream = TcpStream::connect(&address)?;

    let logs = std::fs::read_to_string("logs.txt")?;
    for log in logs.lines() {
        println!("{}", log);
        stream.write_all(format!("{}\n", log).as_bytes())?;
    }

    Ok(())
}
