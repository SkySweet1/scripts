// ------------------------------------------------------- enum -------------------------------------------------------

enum Tool_type {
    Shovel,
    Pick,
    Hand,
}

// ------------------------------------------------------- struct -------------------------------------------------------

struct Block {
    name: String,
    time_to_destruct: std::time::Duration,
    interact: bool,
}

struct Sand {
    base: Block,
    interact_methods: Option<Shovel>,
}

struct Stone {
    base: Block,
    interact_methods: Option<Pick>,
}

// ---------------

struct Tools {
    index: i32,
    name: String,
    tool_type: Tool_type,

}

struct Shovel {
    base: Tools,
}

struct Pick {
    base: Tools,
}

// -------------------------------------------------------- impl -----------------------------------------------------------

impl Block {
    fn new(
        name: &str,
        duration_for_destruct: std::time::Duration,
        interact: bool,
    ) -> Self {
        Self {
            name: name.to_string(),
            time_to_destruct: duration_for_destruct,
            interact: interact,
        }
    }
}

impl Sand {
    fn new_with_tool() -> Self {
        Self {
            interact_methods: Some(Shovel::new()),

            base: Block::new(
                "Sand",
                std::time::Duration::from_secs(1),
                true,
            ),
        }
    }

    fn new_without_tool() -> Self {
        Self {
            interact_methods: None,

            base: Block::new(
                "Sand",
                std::time::Duration::from_secs(1),
                true,
            ),
        }
    }

    fn can_be_mined(&self, player_tool: &Tools) -> bool {
        match player_tool.tool_type {
            Tool_type::Hand => true,
            Tool_type::Pick => false,
            Tool_type::Shovel => true,
        }
    }
    
}

impl Stone {
    fn new_with_tool() -> Self {
        Self {
            interact_methods: Some(Pick::new()),

            base: Block::new(
                "Stone",
                std::time::Duration::from_secs(4),
                true,
            )
        }
    }

    fn new_without_tool() -> Self {
        Self {
            interact_methods: None,

            base: Block::new(
                "Stone",
                std::time::Duration::from_secs(4),
                true,
            )
        }
    }

    fn can_be_mined(&self, player_tool: &Tools) -> bool {
        match player_tool.tool_type {
            Tool_type::Hand => false,
            Tool_type::Pick => true,
            Tool_type::Shovel => false,
        }
    }
}

// ---------------

impl Tools {
    fn new(index: i32, name: &str, tool_type: Tool_type) -> Self {
        Self {
            index: index,
            name: name.to_string(),
            tool_type: tool_type,
        }
    }
}

impl Shovel {
    fn new() -> Self {
        Self {
            base: Tools::new(
                1,
                "Shovel",
                Tool_type::Shovel,
            )
        }
    }
}

impl Pick {
    fn new() -> Self {
        Self {
            base: Tools::new(
                2,
                "Pick",
                Tool_type::Pick,
            )
        }
    }
}

// -------------------------------------------------------- Drop -----------------------------------------------------------

impl Drop for Block {
    fn drop(&mut self) {
        println!("dectructor for {}", self.name);
    }
}

impl Drop for Stone {
    fn drop(&mut self) {
        println!("destructor for {}", self.base.name);
    }
}

impl Drop for Sand {
    fn drop(&mut self) {
        println!("destructor for {}", self.base.name);
    }
}

impl Drop for Tools {
    fn drop(&mut self) {
        println!("destructor for {}, index: {}", self.name, self.index);
    }
}

impl Drop for Shovel {
    fn drop(&mut self) {
        println!("destructor for {}, index: {}", self.base.name, self.base.index);
    }
}

impl Drop for Pick {
    fn drop(&mut self) {
        println!("destructor for {}, index: {}", self.base.name, self.base.index);
    }
}

// -------------------------------------------------------- main --------------------------------------------------

fn main() {}