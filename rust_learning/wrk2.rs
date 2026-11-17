// ----------------------------------------- struct -------------------------------------------------

struct Figure {
    // базовый
    counter_count: i32,
    figure_color: String,
}

struct Triangle {
    // производный от базового
    which_figure: Figure,
    figure_name: String,
}

/*
[Структура Triangle]
  ├── which_figure: [Структура Figure]
  │     ├── counter_count: 3   <--- Вот наше число!
  │     └── figure_color: "красный"
  └── figure_name: "треугольник"
*/

struct Circle {
    // производный от базового
    whitch_figure: Figure,
    figure_name: String,
}

struct Square {
    // производный от базового
    whitch_figure: Figure,
    figure_name: String,
}

// ----------------------------------------- impl -------------------------------------------------

impl Figure { // базовый
    fn new(counter_c: i32, figure_color: String) -> Self {
        Self {
            counter_count: counter_c,
            figure_color: figure_color,
        }
    }

    pub fn count_summ(&self, counter_c: i32) -> Result<i32, String> {
        if counter_c == 0 || counter_c < 0 {
            return Err(String::from("Division by zero!"));
        }

        let mut counter_summ = 0;
        counter_summ += counter_c;

        println!("counter summ: {}", counter_summ);

        Ok(counter_summ)
    }
}

impl Triangle { // производный от базового
    fn new(name: String, color: String, counter_count: i32) -> Self {
        Self {
            which_figure: Figure::new(counter_count, color),
            figure_name: name,
        }
    }
}

impl Circle { // производный от базового
    fn new(name: String, color: String, counter_count: i32) -> Self {
        Self {
            whitch_figure: Figure::new(counter_count, color),
            figure_name: name,
        }
    }
}

impl Square { // производный от базового
    fn new(name: String, color: String, counter_count: i32) -> Self {
        Self {
            whitch_figure: Figure::new(counter_count, color),
            figure_name: name,
        }
    }
}

// --------------------------------------- drop ---------------------------------------------------

impl Drop for Figure {
    fn drop(&mut self) {
        println!("destr main impl");
    }
}

impl Drop for Triangle {
    fn drop(&mut self) {
        println!("destr for {}", self.figure_name);
    }
}

impl Drop for Circle {
    fn drop(&mut self) {
        println!("destr for {}", self.figure_name);
    }
}

impl Drop for Square {
    fn drop(&mut self) {
        println!("destr for {}", self.figure_name);
    }
}

// -------------------------------------- trait Shape ----------------------------------------------------

trait Shape {
    // трейд - соглашение
    fn get_color(&self) -> &String; // "-> ___" это типо что будем возвращать

    fn calc_summ(&self, num: i32) -> Result<i32, String>; // и тут это значит тоже самое
    // &self - только чтение
    fn get_figure_name(&self) -> &String;

    fn get_figure_counter_count(&self) -> &i32;
}

// -------------------------------------- hape for ----------------------------------------------------

impl Shape for Triangle {
    fn get_color(&self) -> &String {
        &self.which_figure.figure_color // уже существующее данное поэтому возвращаем ссылку
    }

    fn calc_summ(&self, num: i32) -> Result<i32, String> {
        self.which_figure.count_summ(num) // а тут мы посчитали новое значение и вернули его
    }

    fn get_figure_name(&self) -> &String {
        &self.figure_name
    }

    fn get_figure_counter_count(&self) -> &i32 {
        &self.which_figure.counter_count
    }
}

impl Shape for Circle {
    fn get_color(&self) -> &String {
        &self.whitch_figure.figure_color
    }

    fn calc_summ(&self, num: i32) -> Result<i32, String> {
        self.whitch_figure.count_summ(num) // дилигирование - не реализуем код сами заново а используем уже готовый метод
    }

    fn get_figure_name(&self) -> &String {
        &self.figure_name
    }

    fn get_figure_counter_count(&self) -> &i32 {
        &self.whitch_figure.counter_count
    }
}

impl Shape for Square {
    fn get_color(&self) -> &String {
        &self.whitch_figure.figure_color
    }

    fn calc_summ(&self, num: i32) -> Result<i32, String> {
        self.whitch_figure.count_summ(num)
    }

    fn get_figure_name(&self) -> &String {
        &self.figure_name
    }

    fn get_figure_counter_count(&self) -> &i32 {
        &self.whitch_figure.counter_count
    }
}

fn main(){
    let tri = Triangle::new(String::from("треугольник"), String::from("красный"), 3);
    let circ = Circle::new(String::from("круг"), String::from("синий"), 0);
    let sq = Square::new(String::from("квадрат"), String::from("желтый"), 4);

    let shapes: Vec<Box<dyn Shape>> = vec![
        Box::new(tri),
        Box::new(circ),
        Box::new(sq),
    ];

    for shape in shapes {
        println!("фигура: {}; цвет: {}, количество углов: {}", 
        shape.get_figure_name(), shape.get_color(), shape.get_figure_counter_count());
    
        let angels = *shape.get_figure_counter_count();

        match shape.calc_summ(angels) {
            Ok(summ) => println!("success: {}", summ),
            Err(error) => println!("errror: {}", error),
        }
    }
}