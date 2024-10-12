
### Database Design

1. **Users Table**
   - **user_id** (PK, INT, AUTO_INCREMENT)
   - **username** (VARCHAR)
   - **password** (VARCHAR)
   - **email** (VARCHAR)
   - **role** (ENUM: 'admin', 'member')
   - **created_at** (DATETIME)

2. **Members Table**
   - **member_id** (PK, INT, AUTO_INCREMENT)
   - **user_id** (FK, INT)
   - **first_name** (VARCHAR)
   - **last_name** (VARCHAR)
   - **date_of_birth** (DATE)
   - **phone_number** (VARCHAR)
   - **membership_start_date** (DATE)
   - **membership_end_date** (DATE)

3. **Attendance Table**
   - **attendance_id** (PK, INT, AUTO_INCREMENT)
   - **member_id** (FK, INT)
   - **date** (DATE)
   - **status** (ENUM: 'present', 'absent')

4. **Payments Table**
   - **payment_id** (PK, INT, AUTO_INCREMENT)
   - **member_id** (FK, INT)
   - **amount** (DECIMAL)
   - **payment_date** (DATE)
   - **payment_method** (ENUM: 'credit_card', 'cash', 'bank_transfer')

5. **Classes Table**
   - **class_id** (PK, INT, AUTO_INCREMENT)
   - **class_name** (VARCHAR)
   - **instructor** (VARCHAR)
   - **schedule_time** (DATETIME)

6. **Class Registrations Table**
   - **registration_id** (PK, INT, AUTO_INCREMENT)
   - **member_id** (FK, INT)
   - **class_id** (FK, INT)
   - **registration_date** (DATE)

7. **Subscriptions Table**
   - **subscription_id** (PK, INT, AUTO_INCREMENT)
   - **member_id** (FK, INT)
   - **type** (ENUM: 'monthly', 'yearly')
   - **status** (ENUM: 'active', 'inactive')
