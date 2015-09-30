/*
Project 1a
iOS Fall 15

Bryan Johnson
bmj29@zips.uakron.edu
*/

/*
Directions: Complete each of the comments with code. Observe what the playground
is telling you as you work.
*/

// declare a constant to store the maximum number of students
// in this course, which is 25
let max = 25

// declare a variable to store the current number of students
// in this course, which is currently 26 (don't ask)
var currentStudents: Int = 24

// print the number of students in the course with a nice message
print("The current number of students in this course is \(currentStudents)")

// print the maximum number of students in the course with a nice message
print("The maximum number of students in this course is \(max)")

// print out whether the number of students in the course is under, over,
// or just right (Hint: looking for an if-statement here)
if currentStudents == max {
    print("The amount of students in this course is just right.")
} else if currentStudents > max {
    print("There are more students than the max allowed in this course.")
} else {
    print("There are fewer students that the max allowed in this course.")
}

// Go up to the declaration and alter the current number of students in the course to see the result

// store the first names of at least 3 students in the course
// Hint: These can be made up
var students: [String] = ["Bandobras Hogg", "Otho Sandheaver", "Mungo Goodenough", "Mirabella Hlothran",
                              "Hilda Gamwich", "Pervinca Headstrong"]

// output the first names of all the students in the course
// Hint: looking for a for-statement here
for (index, student) in students.enumerate() {
    print("Item \(index + 1): \(student)")
}

// for each student, print their name backwards using a switch statement in a for-loop
// Hint: Yes, I know, I wouldn't use a switch statement either, but whatever. You think
// these are easy to come up with?
for student in students {
    switch(student) {
        case "Bandobras Hogg": print("ggoH sarbodnaB")
        case "Otho Sandheaver": print("revaednaS ohtoO")
        case "Mungo Goodenough": print("hguonedooG ognuM")
        case "Mirabella Hlothran": print("narhtolH allebariM")
        case "Hilda Gamwich": print("hciwmaG adliH")
        case "Pervinca Headstrong": print("gnortsdaeH acnivreP")
        default:
            print("Oops.")
    }
}

// write a function (not method) called maxStudents which just returns the maximum number of students
// (25, remember?)
func maxStudents() -> Int {
    return 25
}

// show some calls to maxStudents
maxStudents()
maxStudents()
maxStudents()

// write a function (not method) called getFred which returns the name "Fred" if "Fred" is in the
// string array passed as a parameter, otherwise an empty string is returned
func getFred(names: [String]) -> String {
    if names.contains("Fred") {
        return "Fred"
    }
    return ""
}

// show some calls to getFred
getFred(students)
students.append("Fred")
getFred(students)

// write a function (not method) called findFred which returns the name "Fred" if "Fred" is in the
// string array passed as a parameter, otherwise return nil
func findFred(names: [String]) -> String? {
    if(names.contains("Fred")) {
        return "Fred"
    } else {
        return nil
    }
}

// show some calls to findFred
findFred(students)
students.removeAtIndex(students.indexOf("Fred")!)
findFred(students)

// write a function (not method) called findName which returns a given name (passed as a parameter)
// if it is in the string array passed as a parameter, otherwise return nil
func findName(name: String, names:[String]) -> String? {
    if(names.contains(name)) {
        return name
    } else {
        return nil
    }
}

// show some calls to findName
findName("Bandobras Hogg", names: students)
findName("Fred", names: students)