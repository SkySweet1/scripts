// -------------------------------------------------- struct -------------------------------------------------------

struct School {
    number_of_school: i32,
    name_of_shcool: String,
}

struct Student {
    school: School,
    full_name_of_student: String,
    number_of_student: i32,
    number_of_student_group: i32,
}

struct Human {
    status: Option<Student>,
    name: String,
    age: i32,
}

// -------------------------------------------------- impl --------------------------------------------------

impl School {
    fn new(number: i32, name: &str) -> Result<Self, String> {
        if number <= 0 {
            return Err(String::from("номер школы не может быть отрицательным или быть равным нулю!"));
        }

        Ok(Self {
            number_of_school: number,
            name_of_shcool: name.to_string(),
        })
    }
}

impl Student {
    fn new(
        number_of_student_group: i32,
        full_name_of_student: &str,
        number_of_student: i32,
        name_of_school: &str,
        number_of_school: i32

    ) -> Result<Self, String> {
        if number_of_student_group <= 0 || number_of_student <= 0 || number_of_school <= 0 {
            return Err(String::from("числа не должны быть меньше или равны нулю"));
        }

        Ok(Self {
            number_of_student_group: number_of_student_group,
            full_name_of_student: full_name_of_student.to_string(),
            number_of_student: number_of_student,

            school: School::new(number_of_school, name_of_school)?,
        })
    }
}

impl Human {
    fn new(
        number_of_student_group: i32,
        full_name_of_student: &str,
        number_of_student: i32,
        name_of_school: &str,
        number_of_school: i32,
        name_of_person: &str,
        age_of_person: i32,

    ) -> Result<Self, String> {
        if age_of_person <= 0 {
            return Err(String::from("возраст не может быть отрицательным!"));
        }

        Ok(Self {
            name: name_of_person.to_string(),
            age: age_of_person,

            status: Some(Student::new(
                number_of_student_group, 
                full_name_of_student, 
                number_of_student,
                name_of_school,
                number_of_school,
            )?),
        })
    }

    fn new_just_human(name: &str, age: i32) -> Result<Self, String> {
        if age <= 0 {
            return Err(String::from("возраст не может быть отрицательным!"));
        }

        Ok(Self {
            status: None,
            name: name.to_string(),
            age: age,
        })
    }
}

// ----------------------------------------------- trait ----------------------------------------------

trait Admission { // в трейте нужно писать только сигнатуру
    fn get_admission(&self);

    fn go_to_school(&self);
}

// ----------------------------------------------- trait ----------------------------------------------

impl Admission for Human {
    fn get_admission(&self) {
        println!("{} поступил в школу", self.name);
    }

    fn go_to_school(&self) {
        match &self.status {
            Some(Student) => {
                println!("{} пошел в школу", self.name);
            }

            None => {
                println!("{} не может пойти в школу, он не студент!", self.name);  
            }
        }
    }
}

// ------------------------------------------------ drop ----------------------------------------------

impl Drop for School {
    fn drop(&mut self) {
        println!("школа {} разрушена", self.name_of_shcool);
    }
}

impl Drop for Student {
    fn drop(&mut self) {
        println!("ученик {}, номер {}, школы {}, {} отчислился", 
            self.full_name_of_student, 
            self.number_of_student, 
            self.school.number_of_school, 
            self.school.name_of_shcool
        );
    }
}

impl Drop for Human {
    fn drop(&mut self) {
        println!("человек {} ушел домой", self.name);
    }
}

fn main() {}