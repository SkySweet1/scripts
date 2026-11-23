// ------------------------------ enum ------------------------------

#[derive(Debug)]
enum Errors {
    Server_not_found(String),
    Socket_invalid(i32),
    Bing_invalid(i32),
    Listen_invalid {
        minimum_limit: i32,
        hight_limit: i32,
        current: i32,
    },
    Bad_Gateway(i32),
    No_connection,
}

// ------------------------------ struct ------------------------------

struct Hacker {
    ninkname: String,
    listen_attempt: i32,
    connection: bool,
}

// ------------------------------ impl ------------------------------

impl std::fmt::Display for Errors {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Errors::Server_not_found(server_name) => write!(f, "Server {} not found", server_name),

            Errors::Socket_invalid(socket_index) => write!(f, "Socket ({}) invalid", socket_index),

            Errors::Bing_invalid(bind_number) => write!(f, "Bind ({}), invalid", bind_number),

            Errors::Listen_invalid {
                minimum_limit,
                hight_limit,
                current,
            } => write!(
                f,
                "Listen its between {} and {}. Yours: {}",
                minimum_limit, hight_limit, current,
            ),

            Errors::Bad_Gateway(error) => write!(f, "BadGateway: error {}", error),

            Errors::No_connection => write!(f, "No connection established"),
        }
    }
}

impl Hacker {
    fn new(name: &str, listen_att: i32, conected: bool) -> Self {
        Self {
            ninkname: name.to_string(),
            listen_attempt: listen_att,
            connection: conected,
        }
    }

    fn add_new_server(
        &self,
        server_name: &str,
        socket_num: i32,
        bind_num: i32,

    ) -> Result<String, Errors> {

        let min = 0;
        let max = 100;

        if server_name != "new-server" {
            return Err(Errors::Server_not_found(server_name.to_string()));
        }

        if socket_num <= 0 || socket_num > 100 {
            return Err(Errors::Socket_invalid(socket_num));
        }

        if bind_num <= 0 || bind_num > 100 {
            return Err(Errors::Bing_invalid(bind_num));
        }

        if bind_num < min || bind_num > max {
            return Err(Errors::Listen_invalid {
                minimum_limit: min,
                hight_limit: max,
                current: self.listen_attempt,
            });
        }

        if !self.connection {
            return Err(Errors::No_connection);
        }

        Ok(format!("Seccessfully created new server!"))
    }
}

fn main() {}
