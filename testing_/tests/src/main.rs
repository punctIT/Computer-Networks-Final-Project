#[cfg(test)]
mod tests {
    use std::net::{TcpStream};
    use std::io::{Read, Write,self};
    fn send_message(stream: &mut TcpStream, message: &str) -> io::Result<String> {
        let size = message.len() as u32;
        stream.write_all(&size.to_ne_bytes())?; 
        stream.write_all(message.as_bytes())?;
        let mut len_buf = [0u8; 4];
        stream.read_exact(&mut len_buf)?;
        let resp_len = u32::from_ne_bytes(len_buf) as usize;
        let mut buf = vec![0u8; resp_len];
        stream.read_exact(&mut buf)?;
        Ok(String::from_utf8_lossy(&buf).into_owned())
    }


    #[test]
    fn test_unknown_command() {

        let mut stream = TcpStream::connect("127.0.0.1:8080").unwrap();
        let response = send_message(&mut stream, "typ:ce;").unwrap();
        assert_eq!(response, "succes:false;type:{error};content:{Invalid data: don t containt a type};");
    }
    #[test]
    fn test_invalid_junk_format() {

        let mut stream = TcpStream::connect("127.0.0.1:8080").unwrap();
        let response = send_message(&mut stream, "ceva").unwrap();
        assert_eq!(response, "succes:false;type:{error};content:{Invalid data , not a valid JUNK format \n ceva};");
    }
    #[test]
    fn test_invalid_token() {

        let mut stream = TcpStream::connect("127.0.0.1:8080").unwrap();
        let response = send_message(&mut stream, "type:ceva;").unwrap();
        assert_eq!(response, "succes:{false};type:{Error};content:{Invalid Token};");
    }
    #[test]
    fn test_without_type() {

        let mut stream = TcpStream::connect("127.0.0.1:8080").unwrap();
        let response = send_message(&mut stream, "ceva:ceva;").unwrap();
        assert_eq!(response, "succes:false;type:{error};content:{Invalid data: don t containt a type};");
    }
    #[test]
    fn test_invalid_login(){
        let mut stream = TcpStream::connect("127.0.0.1:8080").unwrap();
        let response = send_message(&mut stream, "type:login;username:;password:1;").unwrap();
        assert_eq!(response, "succes:{false};type:{login};content:{Invalid username or password};");
    }
    #[test]
    fn test_valid_login(){
        let mut stream = TcpStream::connect("127.0.0.1:8080").unwrap();
        let response = send_message(&mut stream, "type:login;username:1;password:1;").unwrap();
        if !response.starts_with("succes:{true};type:{login};"){
            panic!("Invalid login");
        }
        
    }
    
}
fn main(){

}