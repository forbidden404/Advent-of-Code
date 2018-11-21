import Foundation

let input = readLine()

var floor = 0
var position = 0
var hasFoundPosition = false

guard let input = input else { throw NSError() }

for character in input {
    if character == "(" {
        floor += 1
    } else if character == ")" {
        floor -= 1
    }

    if !hasFoundPosition {
        position += 1

        if floor == -1 {
            hasFoundPosition = true
        }
    }
}

print(floor)
print(position)
