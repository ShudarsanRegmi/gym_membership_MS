-- schema creation flies

CREATE TABLE Users (
    user_id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL,
    password TEXT NOT NULL,
    email TEXT NOT NULL,
    role TEXT CHECK(role IN ('admin', 'member')) NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE Members (
    member_id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER,
    first_name TEXT NOT NULL,
    last_name TEXT NOT NULL,
    date_of_birth DATE NOT NULL,
    phone_number TEXT,
    membership_start_date DATE NOT NULL,
    membership_end_date DATE NOT NULL,
    FOREIGN KEY (user_id) REFERENCES Users(user_id) ON DELETE CASCADE
);

CREATE TABLE Attendance (
    attendance_id INTEGER PRIMARY KEY AUTOINCREMENT,
    member_id INTEGER,
    date DATE NOT NULL,
    status TEXT CHECK(status IN ('present', 'absent')) NOT NULL,
    FOREIGN KEY (member_id) REFERENCES Members(member_id) ON DELETE CASCADE
);

CREATE TABLE Payments (
    payment_id INTEGER PRIMARY KEY AUTOINCREMENT,
    member_id INTEGER,
    amount REAL NOT NULL,
    payment_date DATE NOT NULL,
    payment_method TEXT CHECK(payment_method IN ('credit_card', 'cash', 'bank_transfer')) NOT NULL,
    FOREIGN KEY (member_id) REFERENCES Members(member_id) ON DELETE CASCADE
);

CREATE TABLE Classes (
    class_id INTEGER PRIMARY KEY AUTOINCREMENT,
    class_name TEXT NOT NULL,
    instructor TEXT NOT NULL,
    schedule_time DATETIME NOT NULL
);

CREATE TABLE Class_Registrations (
    registration_id INTEGER PRIMARY KEY AUTOINCREMENT,
    member_id INTEGER,
    class_id INTEGER,
    registration_date DATE NOT NULL,
    FOREIGN KEY (member_id) REFERENCES Members(member_id) ON DELETE CASCADE,
    FOREIGN KEY (class_id) REFERENCES Classes(class_id) ON DELETE CASCADE
);

CREATE TABLE Subscriptions (
    subscription_id INTEGER PRIMARY KEY AUTOINCREMENT,
    member_id INTEGER,
    type TEXT CHECK(type IN ('monthly', 'yearly')) NOT NULL,
    status TEXT CHECK(status IN ('active', 'inactive')) NOT NULL,
    FOREIGN KEY (member_id) REFERENCES Members(member_id) ON DELETE CASCADE
);

CREATE TABLE GymDetails (
    gym_detail_id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    height_cm DECIMAL(5, 2) NOT NULL,  -- Height in centimeters
    weight_kg DECIMAL(5, 2) NOT NULL,  -- Weight in kilograms
    body_fat_percentage DECIMAL(5, 2), -- Optional field for body fat percentage
    bmi DECIMAL(5, 2),                 -- Calculated BMI
    workout_frequency ENUM('daily', 'weekly', 'monthly') NOT NULL,
    goals TEXT,                        -- Fitness goals of the user
    injuries TEXT,                     -- Any previous injuries
    medical_conditions TEXT,           -- Relevant medical conditions
    FOREIGN KEY (user_id) REFERENCES Users(user_id) ON DELETE CASCADE
);

CREATE TABLE GymDetails (
    gym_detail_id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    height_cm REAL NOT NULL,  -- Height in centimeters
    weight_kg REAL NOT NULL,   -- Weight in kilograms
    body_fat_percentage REAL,   -- Optional field for body fat percentage
    bmi REAL,                   -- Calculated BMI
    workout_frequency TEXT NOT NULL CHECK(workout_frequency IN ('daily', 'weekly', 'monthly')), -- Using CHECK constraint for workout frequency
    goals TEXT,                -- Fitness goals of the user
    injuries TEXT,             -- Any previous injuries
    medical_conditions TEXT,   -- Relevant medical conditions
    FOREIGN KEY (user_id) REFERENCES Users(user_id) ON DELETE CASCADE
);

CREATE TABLE Activities (
    activity_id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    activity_type TEXT NOT NULL CHECK(activity_type IN ('workout', 'payment', 'attendance', 'subscription', 'class_registration')),
    activity_date DATETIME DEFAULT CURRENT_TIMESTAMP,
    description TEXT,  -- Optional field to describe the activity
    FOREIGN KEY (user_id) REFERENCES Users(user_id) ON DELETE CASCADE
);

/*
CREATE TABLE UserPersonalInfo (
    personal_info_id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    full_name TEXT NOT NULL,  -- Use TEXT instead of VARCHAR
    father_name TEXT,
    mother_name TEXT,
    date_of_birth DATE NOT NULL,
    age INTEGER GENERATED ALWAYS AS (strftime('%Y', 'now') - strftime('%Y', date_of_birth)) VIRTUAL,
    gender TEXT NOT NULL CHECK(gender IN ('male', 'female', 'other')), -- Using CHECK constraint for gender
    address TEXT,
    phone_number TEXT,        -- Use TEXT instead of VARCHAR for phone number
    FOREIGN KEY (user_id) REFERENCES Users(user_id) ON DELETE CASCADE
);
*/
CREATE TABLE UserPersonalInfo (
    personal_info_id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    full_name TEXT NOT NULL,  
    father_name TEXT,
    mother_name TEXT,
    date_of_birth DATE NOT NULL,
    gender TEXT NOT NULL CHECK(gender IN ('male', 'female', 'other')),
    address TEXT,
    phone_number TEXT,  
    FOREIGN KEY (user_id) REFERENCES Users(user_id) ON DELETE CASCADE
);


-- Insert into Users
INSERT INTO Users (username, password, email, role) VALUES
('john_doe', 'password123', 'john_doe@example.com', 'member'),
('jane_doe', 'password123', 'jane_doe@example.com', 'member'),
('admin_user', 'adminpass', 'admin@example.com', 'admin'),
('mike_smith', 'password123', 'mike_smith@example.com', 'member'),
('sara_jones', 'password123', 'sara_jones@example.com', 'member'),
('chris_evans', 'password123', 'chris_evans@example.com', 'member'),
('laura_lee', 'password123', 'laura_lee@example.com', 'member'),
('daniel_brown', 'password123', 'daniel_brown@example.com', 'member'),
('kelly_white', 'password123', 'kelly_white@example.com', 'member'),
('steve_black', 'password123', 'steve_black@example.com', 'admin');

-- Insert into Members
INSERT INTO Members (user_id, first_name, last_name, date_of_birth, phone_number, membership_start_date, membership_end_date) VALUES
(1, 'John', 'Doe', '1990-05-15', '555-1234', '2024-01-01', '2024-12-31'),
(2, 'Jane', 'Doe', '1992-08-10', '555-5678', '2024-01-01', '2024-12-31'),
(4, 'Mike', 'Smith', '1985-03-22', '555-8765', '2024-01-01', '2024-12-31'),
(5, 'Sara', 'Jones', '1988-07-30', '555-4321', '2024-01-01', '2024-12-31'),
(6, 'Chris', 'Evans', '1995-02-18', '555-9876', '2024-01-01', '2024-12-31'),
(7, 'Laura', 'Lee', '1993-09-25', '555-2468', '2024-01-01', '2024-12-31'),
(8, 'Daniel', 'Brown', '1990-11-17', '555-1357', '2024-01-01', '2024-12-31'),
(9, 'Kelly', 'White', '1987-04-13', '555-9753', '2024-01-01', '2024-12-31');

-- Insert into Attendance
INSERT INTO Attendance (member_id, date, status) VALUES
INSERT INTO Attendance (member_id, date, status) VALUES(1, '2024-10-10', 'present'),(2, '2024-10-10', 'present'),(3, '2024-10-10', 'absent'),(4, '2024-10-10', 'present'),(5, '2024-10-10', 'present'),(6, '2024-10-10', 'absent'),(7, '2024-10-10', 'present'),(8, '2024-10-10', 'present'),(9, '2024-10-10', 'absent'),(10, '2024-10-10', 'present'),(1, '2024-10-11', 'present'),(2, '2024-10-11', 'absent'),(3, '2024-10-11', 'present'),(4, '2024-10-11', 'present'),(5, '2024-10-11', 'absent'),(6, '2024-10-11', 'present'),(7, '2024-10-11', 'present'),(8, '2024-10-11', 'absent'),(9, '2024-10-11', 'present'),(10, '2024-10-11', 'present'),(1, '2024-10-12', 'absent'),(2, '2024-10-12', 'present'),(3, '2024-10-12', 'present'),(4, '2024-10-12', 'absent'),(5, '2024-10-12', 'present'),(6, '2024-10-12', 'absent'),(7, '2024-10-12', 'present'),(8, '2024-10-12', 'present'),(9, '2024-10-12', 'absent'),(10, '2024-10-12', 'present'),(1, '2024-10-13', 'present'),(2, '2024-10-13', 'present'),(3, '2024-10-13', 'absent'),(4, '2024-10-13', 'present'),(5, '2024-10-13', 'absent'),(6, '2024-10-13', 'present'),(7, '2024-10-13', 'present'),(8, '2024-10-13', 'absent'),(9, '2024-10-13', 'present'),(10, '2024-10-13', 'absent'),(1, '2024-10-14', 'present'),(2, '2024-10-14', 'absent'),(3, '2024-10-14', 'present'),(4, '2024-10-14', 'absent'),(5, '2024-10-14', 'present'),(6, '2024-10-14', 'absent'),(7, '2024-10-14', 'present'),(8, '2024-10-14', 'present'),(9, '2024-10-14', 'absent'),(10, '2024-10-14', 'present'),(1, '2024-10-15', 'absent'),(2, '2024-10-15', 'present'),(3, '2024-10-15', 'present'),(4, '2024-10-15', 'present'),(5, '2024-10-15', 'absent'),(6, '2024-10-15', 'present'),(7, '2024-10-15', 'present'),(8, '2024-10-15', 'absent'),(9, '2024-10-15', 'present'),(10, '2024-10-15', 'present'),(1, '2024-10-16', 'present'),(2, '2024-10-16', 'present'),(3, '2024-10-16', 'absent'),(4, '2024-10-16', 'present'),(5, '2024-10-16', 'present'),(6, '2024-10-16', 'absent'),(7, '2024-10-16', 'present'),(8, '2024-10-16', 'present'),(9, '2024-10-16', 'absent'),(10, '2024-10-16', 'present'),(1, '2024-10-17', 'absent'),(2, '2024-10-17', 'present'),(3, '2024-10-17', 'present'),(4, '2024-10-17', 'absent'),(5, '2024-10-17', 'present'),(6, '2024-10-17', 'present'),(7, '2024-10-17', 'present'),(8, '2024-10-17', 'absent'),(9, '2024-10-17', 'present'),(10, '2024-10-17', 'absent');

-- Insert into Payments
INSERT INTO Payments (member_id, amount, payment_date, payment_method) VALUES
(1, 50.00, '2024-01-01', 'credit_card'),
(2, 50.00, '2024-01-01', 'cash'),
(4, 50.00, '2024-01-01', 'bank_transfer'),
(5, 50.00, '2024-01-01', 'credit_card'),
(6, 50.00, '2024-01-01', 'cash'),
(7, 50.00, '2024-01-01', 'credit_card'),
(8, 50.00, '2024-01-01', 'bank_transfer'),
(9, 50.00, '2024-01-01', 'cash');

-- Insert into Classes
INSERT INTO Classes (class_name, instructor, schedule_time) VALUES
('Yoga', 'Alice Brown', '2024-10-16 10:00:00'),
('Pilates', 'Bob Green', '2024-10-16 12:00:00'),
('Zumba', 'Charlie Black', '2024-10-16 14:00:00');

-- Insert into Class_Registrations
INSERT INTO Class_Registrations (member_id, class_id, registration_date) VALUES
(1, 1, '2024-10-10'),
(2, 2, '2024-10-10'),
(4, 3, '2024-10-10'),
(5, 1, '2024-10-10'),
(6, 2, '2024-10-10'),
(7, 3, '2024-10-10'),
(8, 1, '2024-10-10'),
(9, 2, '2024-10-10');

-- Insert into Subscriptions
INSERT INTO Subscriptions (member_id, type, status) VALUES
(1, 'monthly', 'active'),
(2, 'yearly', 'active'),
(4, 'monthly', 'active'),
(5, 'monthly', 'inactive'),
(6, 'yearly', 'active'),
(7, 'monthly', 'active'),
(8, 'yearly', 'active'),
(9, 'monthly', 'inactive');

-- Insert into GymDetails
INSERT INTO GymDetails (user_id, height_cm, weight_kg, body_fat_percentage, bmi, workout_frequency, goals, injuries, medical_conditions) VALUES
(1, 175.0, 70.5, 18.5, 23.0, 'daily', 'Build muscle', NULL, NULL),
(2, 160.0, 60.0, 20.0, 23.4, 'weekly', 'Lose weight', NULL, NULL),
(4, 180.0, 85.0, 25.0, 26.2, 'daily', 'Maintain health', NULL, NULL),
(5, 170.0, 68.0, 22.0, 23.5, 'monthly', 'Increase endurance', 'Knee injury', 'Asthma'),
(6, 165.0, 65.0, 21.0, 23.9, 'weekly', 'Stay fit', NULL, NULL),
(7, 172.0, 72.0, 19.0, 24.3, 'daily', 'Tone body', 'Shoulder injury', NULL),
(8, 168.0, 70.0, 20.0, 24.8, 'weekly', 'Increase strength', NULL, NULL),
(9, 182.0, 78.0, 18.0, 25.0, 'monthly', 'Maintain flexibility', NULL, 'Hypertension');

-- Insert into UserPersonalInfo
INSERT INTO UserPersonalInfo (user_id, full_name, father_name, mother_name, date_of_birth, gender, address, phone_number) VALUES
(1, 'John Doe', 'Robert Doe', 'Nancy Doe', '1990-01-15', 'male', '123 Main St, Springfield', '1234567890'),
(2, 'Jane Doe', 'Michael Doe', 'Lisa Doe', '1992-05-22', 'female', '456 Oak Ave, Springfield', '9876543210'),
(3, 'Admin User', NULL, NULL, '1985-08-30', 'male', '789 Elm St, Springfield', '1122334455'),
(4, 'Mike Smith', 'David Smith', 'Emma Smith', '1988-03-12', 'male', '321 Pine St, Springfield', '2233445566'),
(5, 'Sara Jones', 'Brian Jones', 'Sophia Jones', '1995-07-09', 'female', '654 Maple St, Springfield', '3344556677'),
(6, 'Chris Evans', 'William Evans', 'Olivia Evans', '1993-11-21', 'male', '987 Birch St, Springfield', '4455667788'),
(7, 'Laura Lee', 'George Lee', 'Mia Lee', '1996-02-25', 'female', '147 Cedar St, Springfield', '5566778899'),
(8, 'Daniel Brown', 'Richard Brown', 'Chloe Brown', '1991-09-17', 'male', '369 Willow St, Springfield', '6677889900'),
(9, 'Kelly White', 'James White', 'Isabella White', '1994-12-04', 'female', '258 Poplar St, Springfield', '7788990011'),
(10, 'Steve Black', 'Patrick Black', 'Ella Black', '1983-06-19', 'male', '147 Ash St, Springfield', '8899001122');

/*
-- Deleting all records and also reset the auto incre counter
DELETE FROM Attendance;
DELETE FROM sqlite_sequence WHERE name='Attendance';
/*


