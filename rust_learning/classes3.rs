// ----------------------------------------- struct ----------------------------------------------------
struct Figure {
    counter_count: i32, // количество углов
    number_of_figure: i32, // номер фигуры
}

struct Circle {
    include: Figure, // количество углов и номер фигуры
    name_of_figure: String, // имя фигуры
}

// ----------------------------------------- impl ----------------------------------------------------

impl Figure {
    fn new(count_of_counters: i32, number: i32) -> Result<Self, String> {
        if number < 0 {
            return Err(String::from("Less than zero!"));
        }

        Ok(Self {
            counter_count: count_of_counters,
            number_of_figure: number,
        })
    }
    /*
        если число < 0 то создаеться обьект
    */

    pub fn calc_summ(&self, num: i32) -> Result<i32, String> {
        if num < 0 || num == 0 {
            return Err(String::from("it must be higher than zero!"));
        }

        Ok(num)
    }
}

impl Circle {
    fn new(name: &str, counters_of_figure: i32, number: i32) -> Result<Self, String> {
        Ok( Self {
            include: Figure::new(counters_of_figure, number)?,
            name_of_figure: name.to_string(),
        })
    }
}

// ----------------------------------------- trait Shape ----------------------------------------------------

trait Shape {
    fn calc(&self, num: i32) -> Result<i32, String>;
    fn num_of_figure(&self) -> &i32;
    fn name_of_figure(&self) -> &str;
}

// ----------------------------------------- Shape for ----------------------------------------------------

impl Shape for Circle {
    fn calc(&self, num: i32) -> Result<i32, String> {
        self.include.calc_summ(num)
    }

    fn name_of_figure(&self) -> &str {
        &self.name_of_figure
    }

    fn num_of_figure(&self) -> &i32 {
        &self.include.number_of_figure
    }
}

// ----------------------------------------- drop ----------------------------------------------------

impl Drop for Figure {
    fn drop(&mut self) {
        println!("destruct for {} object", self.number_of_figure);
    }
}

impl Drop for Circle {
    fn drop(&mut self) {
        println!("destructor for {}", self.name_of_figure);
    }
}

fn main() {
    let circ = match Circle::new("круг", 0, 1) {
        Ok(circle) => circle,
        Err(error) => {
            println!("item was not created: {}", error);
            return;
        }
    };

    println!("название: {}, количество углов: {}, номер фигуры: {}", circ.name_of_figure, circ.include.counter_count, circ.include.number_of_figure); // тут недописал просто т к нету полей почему-то
    
    print!("сумма углов: ");

    match circ.calc(circ.include.counter_count) {
        Ok(summ) => println!("{}", summ),
        Err(error) => println!("error: {}", error),
    }

    println!("Через трейт: {} (номер {})", 
        circ.name_of_figure(), 
        circ.num_of_figure()
    );
}
