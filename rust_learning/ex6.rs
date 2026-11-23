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
    fn fmt(&self, form: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
    /*  

    fmt - сокращение от format (буфер записи)

    std::fmt::Formater - Специальная структура которая умеет собирать строки - работает как буфер

    <'_> - время жизни обьекта - компилятор требует гарантию что этот Formater будет жить в памяти ровно столько 
    сколько нужно для форматирования - символы '_ означают "анонимное время жизни"
    
    Formatter - это временный обьект который одалживает реальный поток вывода


    std::fmt::Result - возвращаемый тип - вроде как работает как Result<(), std::fmt::Error> -
    метод либо вернет пустоту либо ошибку форматирования

    */


        match self {
            HackError::Server_not_found(name) => write!(form, "Server {} not found", name),

            HackError::Low_skill { required, current } => {
                write!(form, "You dont have enough skill! you have: {}, requirement: {}", required, current)
            }

            HackError::Ice_detected => write!(form, "Warning: ICE detected! power off"),
        }
        /*
        match self - смотри на саму ошибку и сопоставляем варианты enum

        write! - важный макрос - println! печатает текст в консоль а write! печатает текст в первый аргумент form

            если бы мы написали println! текст улетел бы сразу в консоль минуя буфер form

            если бы мы написали format!, Rust бы выделел память в куче и создал бы временну строку String, скопировал 
            бы туда текст а потом fmt скопировал бы этот текстиз временной строки в буфер form - это медленно и создает мусор для сборщика мусора


            write!(form, ...) пишет текст напрямую в буфер form минуя создание промежуточных строк

            это называется Zero-Allocation formatting. Rust делает это чтобы печать тысяч ошибок в лог-файл не вызвала тормозов изза постоянных аллокаций памяти
        */
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