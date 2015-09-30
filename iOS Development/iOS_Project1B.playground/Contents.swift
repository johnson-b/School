/*
Project 1b
iOS Fall 15

Bryan Johnson
bmj29@zips.uakron.edu
*/

class Dog {
    var name: String
    var gender: String
    var age: Int = 0
    var humanAge: Int {
        if(self.age >= 2) {
            return 21 + ((self.age - 2) * 4)
        } else {
            var temp = Double(self.age)
            temp = temp * 10.5
            return Int(temp)
        }
    }
    var birthDay: Int = 1
    var birthMonth: Int = 1
    var birthYear: Int = 1972
    var birthDate: String {
        get {
            let day = String(self.birthDay) + ", "
            return calcBirthMonth() + day + String(self.birthYear)
        }
    }
    
    func speak() -> String {
        return "Woof"
    }
    
    func calcBirthMonth() -> String {
        switch(self.birthMonth) {
            case 1: return "January "
            case 2: return "February "
            case 3: return "March "
            case 4: return "April "
            case 5: return "May "
            case 6: return "June "
            case 7: return "July "
            case 8: return "August "
            case 9: return "September "
            case 10: return "October "
            case 11: return "November "
            case 12: return "December "
            default: return "NULL "
        }
    }
    
    init() {
        name = "No Name"
        gender = "M"
    }
    
    init(name: String, gender: String) {
        self.name = name
        self.gender = gender
    }
    
    deinit {
        age = 0
    }
}

var dog = Dog(name: "Kujo", gender: "M")
dog.age = 3
dog.birthDay = 11
dog.birthMonth = 8
dog.birthYear = 2012
print("The dog's name is \(dog.name)")
print("\(dog.name)'s gender is '\(dog.gender)'")
print("\(dog.name) was born on \(dog.birthDate)")
print("\(dog.name) is \(dog.age) years old")
print("In human years, \(dog.name) is \(dog.humanAge) years old")
print("\(dog.name) says hello: \(dog.speak())!")
