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

