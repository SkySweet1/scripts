// ------------------------------ custom type of error ------------------------------

#[derive(Debug)]
enum HackError {
    Server_not_found(String),

    Low_skill { required: u32, current: u32 },

    Ice_detected,
}

// ------------------------------------ struct ----------------------------------------

struct Hacker {
    nickname: String,
    skill_level: u32,
}

// ------------------------------------- impl ----------------------------------------

impl std::fmt::Display for HackError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            HackError::Server_not_found(name) => write!(f, "Server {} not found", name),

            HackError::Low_skill { required, current } => {
                write!(f, "You dont have enough skill! you have: {}, requirement: {}", required, current)
            }

            HackError::Ice_detected => write!(f, "Warning: ICE detected! power off"),
        }
    }
}

impl Hacker {
    fn new(nickname: &str, skill: u32) -> Self {
        Self {
            nickname: nickname.to_string(),
            skill_level: skill,
        }
    }

    fn hack_server(&self, target_name: &str, required_skill: u32) -> Result<String, HackError> {
        if target_name == "Arasaka Mainframe" {
            return Err(HackError::Ice_detected);
        }

        if self.skill_level < required_skill {
            return Err(HackError::Low_skill { required: required_skill, current: self.skill_level });
        }

        if target_name == "ghost_node" {
            return Err(HackError::Server_not_found(target_name.to_string()));
        }

        Ok(format!("Successfully downloaded 500 gb date from {}", target_name))
    }
}

impl std::error::Error for HackError {}

fn main() {}