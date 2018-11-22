fn main() {
    use std::io::stdin;
    
    let mut floor = 0;
    let mut position = 0;
    let mut has_found_position = false;

    let mut input = String::new();
    stdin().read_line(&mut input).expect("Wrong input");

    for c in input.chars() {
        if c == '(' {
            floor += 1;
        } else if c == ')' {
            floor -= 1;
        }

        if !has_found_position {
            position += 1;

            if floor == -1 {
                has_found_position = true;
            }
        }
    }

    println!("{}", floor);
    println!("{}", position);
}
