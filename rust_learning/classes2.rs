struct Student {
    name: String,
    age: u32,
}

impl Student {
    fn new(name: String, age: u32) -> Self {
        Self { name, age }
    }

    fn greet(&self){
        println!("hello, im {}, im {} old", self.name, self.age);
    }
}

fn main(){
    let student1 = Student::new(String::from("dmitry"), 20);

    student1.greet();
}