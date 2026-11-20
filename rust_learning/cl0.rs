// Аналог класса в C++. Только данные.
struct User {
    name: String, // Аналог std::string
    age: u32,     // Беззнаковое целое (unsigned int)
}

// Аналог блока с методами класса.
impl User {
    // Конструктор. В C++ это был бы метод User(...)
    fn new(name: String, age: u32) -> Self {
        // Создаем и возвращаем экземпляр.
        // В Rust можно писать сокращенно: Self { name, age },
        // если имена переменных совпадают с именами полей.
        Self {
            name: name,
            age: age,
        }
    }

    // Аналог const-метода (void greet() const).
    // &self означает "взять объект по неизменяемой ссылке".
    fn greet(&self) {
        println!("Привет, меня зовут {}!", self.name);
    }

    // Аналог обычного метода, который меняет состояние.
    // &mut self означает "взять объект по изменяемой ссылке".
    fn have_birthday(&mut self) {
        self.age += 1;
        println!("Теперь мне {} лет.", self.age);
    }

    fn change_name(&mut self, new_name: String) {
        self.name = new_name;
    }
}

fn main() {
    // Создаем экземпляр структуры.
    // Обрати внимание на `mut`. Без него мы не сможем вызвать have_birthday,
    // потому что она требует изменяемую ссылку (&mut self).
    let mut user1 = User::new(String::from("Иван"), 20);

    // Вызываем методы через точку, как в C++ или Python.
    user1.greet();
    user1.have_birthday();
    user1.greet(); // Проверим, что возраст изменился

    user1.change_name(String::from("Александр"));
    user1.greet(); 
}
