#[derive(Debug)]
enum Errors {
    Hack_error(String),
}

struct Hacker {
    nickname: String,
}

impl std::fmt::Display for Errors {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Errors::Hack_error(error) => write!(f, "hack error: {}", error),
        }
    }
}

impl Hacker {
    fn new(name: &str) -> Self {
        Self {
            nickname: name.to_string(),
        }
    }

    fn hack_attempt(&self, server_name: &str) -> Result<String, Errors> {
        if server_name != "server" {
            return Err(Errors::Hack_error(server_name));
        }

        Ok(format!("Success!"))
    }
}

fn main() {}
