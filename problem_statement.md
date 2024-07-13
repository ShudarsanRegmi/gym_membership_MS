13. Gym Membership Management System
Project Goal:
Develop a desktop application for a gym to manage memberships, schedule classes, and track
member attendance. This application will be implemented using C++ or Python with a DBMS
(MySQL or Oracle) for data storage and utilize object-oriented programming concepts.
Target Users:
•Gym staff responsible for managing memberships, scheduling classes, and tracking
attendance.
Core Functionalities:
•••Object-Oriented•••Membership Management:
• Manage different membership types (duration, fees) and handle member registrations
with personal information and chosen membership details.
• Allow functionalities for member profile updates and membership renewals.
Class Scheduling:4. Attendance (Optional):
• Columns: AttendanceID (primary key), MemberID (foreign key references
Members.MemberID), ClassID (foreign key references Classes.ClassID), Date.
5. Bookings (Optional - for member class reservations):
•Columns: BookingID (primary key), MemberID (foreign key references
Members.MemberID), ClassID (foreign key references Classes.ClassID), Date.
• Manage class schedules with information like name, instructor, date, time, and
capacity.
• Offer functionalities for adding new classes and editing existing schedules.
Member Attendance:
••Track member attendance for each class session.
Integrate functionalities for members to book spots in desired classes (optional).
Design:
Member: Class representing a gym member with attributes like name, contact information,
membership details (type, start date, end date).
Class: Class representing a gym class with attributes like name, description, instructor, date,
time, capacity.
Attendance: Class representing member attendance for a specific class session (optional,
can be linked to Member and Class classes).
Database Tables:
1. Members:
• Columns: MemberID (primary key), Name, Contact Information.
2. Memberships:
• Columns: MembershipID (primary key), MemberID (foreign key references
Members.MemberID), Type, StartDate, EndDate, Fee (data type depends on
currency).
3. Classes:
•Columns: ClassID (primary key), Name, Description, Instructor, Date, Time,
Capacity.
4. Attendance (Optional):
• Columns: AttendanceID (primary key), MemberID (foreign key references
Members.MemberID), ClassID (foreign key references Classes.ClassID), Date.
5. Bookings (Optional - for member class reservations):
•Columns: BookingID (primary key), MemberID (foreign key references
Members.MemberID), ClassID (foreign key references Classes.ClassID), Date.
