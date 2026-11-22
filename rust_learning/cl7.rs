// ------------------------------ enum ------------------------------

#[derive(Debug)]
enum Errors {
    Server_not_found(String),
    Socket_invalid(String),
    Bing_invalid(String),
    listen_invalid {
        minimum_limit: i32,
        hight_limit: i32,
    },
    Firewall_detected,
}

// ------------------------------ struct ------------------------------

struct Hacker {
    ninkname: String,
    listen_attempt: i32,
}

// ------------------------------ impl ------------------------------

impl std::fmt::Display for Errors {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Errors::Server_not_found(server_name) => write!(f, "Server {} not found", server_name),

            Errors::Socket_invalid(socket_index) => write!(f, "Socket ({}) invalid", socket_index),

            Errors::Bing_invalid(bind_number) => write!(f, "Bind ({}), invalid", bind_number),
        }
    }
}
