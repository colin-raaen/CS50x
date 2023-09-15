-- Keep a log of any SQL queries you execute as you solve the mystery.
// SUSPECTS: Bruce, Luca, Kelsey, Sofia
//

// SQL Query 1: Initial SQL query to get description of crime scene report

SELECT description
   ...> FROM crime_scene_reports
   ...> WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';
+-------------------------------------------------------------------------------------------
|      description
+-------------------------------------------------------------------------------------------
| Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
Interviews were conducted today with three witnesses who were present at the time
– each of their interview transcripts mentions the bakery. |
| Littering took place at 16:36. No known witnesses.
+-------------------------------------------------------------------------------------------

//SQL Query 2: Query of bakery shop security log
SELECT *
   ...> FROM bakery_security_logs
   ...> WHERE month = 7 AND day = 28;
| id  | year | month | day | hour | minute | activity | license_plate |
| 258 | 2021 | 7     | 28  | 10   | 8      | entrance | R3G7486       |
| 259 | 2021 | 7     | 28  | 10   | 14     | entrance | 13FNH73       |
| 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
| 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
| 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
| 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
| 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
| 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
| 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
| 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
| 268 | 2021 | 7     | 28  | 10   | 35     | exit     | 1106N58

// 3 Query: License plates that exited around time of crime at bakery
//Vanessa exited 10:16
SELECT *
   ...> FROM people
   ...> WHERE license_plate = '5P2BI95';
+--------+---------+----------------+-----------------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate |
+--------+---------+----------------+-----------------+---------------+
| 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
// Bruce exited 10:18
SELECT *
   ...> FROM people
   ...> WHERE license_plate = '94KL13X';
+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+-------+----------------+-----------------+---------------+
// Barry exited 10:18
SELECT *
   ...> FROM people
   ...> WHERE license_plate = '6P58WS2';
+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 243696 | Barry | (301) 555-4174 | 7526138472      | 6P58WS2       |
// Luca exited 10:19
SELECT *
   ...> FROM people
   ...> WHERE license_plate = '4328GD8';
+--------+------+----------------+-----------------+---------------+
|   id   | name |  phone_number  | passport_number | license_plate |
+--------+------+----------------+-----------------+---------------+
| 467400 | Luca | (389) 555-5198 | 8496433585      | 4328GD8       |
//Sophia left 10:20
SELECT * FROM people WHERE license_plate = 'G412CB7';
+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 398010 | Sofia | (130) 555-0289 | 1695452385      | G412CB7       |
// Iman left at 10:21
SELECT * FROM people WHERE license_plate = 'L93JTIZ';
+--------+------+----------------+-----------------+---------------+
|   id   | name |  phone_number  | passport_number | license_plate |
+--------+------+----------------+-----------------+---------------+
| 396669 | Iman | (829) 555-5269 | 7049073643      | L93JTIZ       |
// Diana left at 10:23
SELECT *
   ...> FROM people
   ...> WHERE license_plate = '322W7JE';
+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
// Kelsey left at 10:23
SELECT * FROM people WHERE license_plate = '0NTHK55';
+--------+--------+----------------+-----------------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate |
+--------+--------+----------------+-----------------+---------------+
| 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
+--------+--------+----------------+-----------------+---------------+

// SQL Query: check passenger match on flights from passport numbers
SELECT *
   ...> FROM flights
   ...> JOIN passengers
   ...> ON passengers.flight_id = flights.id
   ...> WHERE flights.month = 7 AND flights.day = 28 AND passengers.passport_number IN ('2963008352', '5773159633', '7526138472', '8496433585', '1695452385', '7049073643', '3592750733', '8294398571');
+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | flight_id | passport_number | seat |
+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
| 20 | 6                 | 8                      | 2021 | 7     | 28  | 15   | 22     | 20        | 2963008352      | 6B   |
+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
// Get name again from passport number Vaness elimiated due to flight time, wasn't in fiftyville
SELECT name
   ...> FROM people
   ...> WHERE passport_number = 2963008352;
+---------+
|  name   |
+---------+
| Vanessa |
+---------+

//Flights with matching passport day after theft
SELECT *
   ...> FROM flights
   ...> JOIN passengers
   ...> ON passengers.flight_id = flights.id
   ...> WHERE flights.month = 7 AND flights.day = 29 AND passengers.passport_number IN ('2963008352', '5773159633', '7526138472', '8496433585', '1695452385', '7049073643', '3592750733', '8294398571');
+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | flight_id | passport_number | seat |
+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
| 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      | 18        | 3592750733      | 4C   |
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 1695452385      | 3B   |
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 5773159633      | 4A   |
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 8294398571      | 6C   |
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 8496433585      | 7B   |
+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+

// Passport Matched day before theft
SELECT *
   ...> FROM flights
   ...> JOIN passengers
   ...> ON passengers.flight_id = flights.id
   ...> WHERE flights.month = 7 AND flights.day = 27 AND passengers.passport_number IN ('2963008352', '5773159633', '7526138472', '8496433585', '1695452385', '7049073643', '3592750733', '8294398571');
+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | flight_id | passport_number | seat |
+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
| 26 | 2                 | 8                      | 2021 | 7     | 27  | 13   | 32     | 26        | 7049073643      | 2C   |
| 39 | 5                 | 8                      | 2021 | 7     | 27  | 22   | 37     | 39        | 2963008352      | 8C   |
+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+

// Interviews from day of theft
SELECT *
   ...> FROM interviews
   ...> WHERE month = 7 AND day = 28;
+-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| id  |  name   | year | month | day |                                                                                                                                                     transcript                                                                                                                                                      |
+-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+                                                                                                                                                                                  |                                                                                                                 |
| 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
+-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

//Who made a phone call right after the theft
SELECT *
   ...> FROM phone_calls
   ...> WHERE month = 7 AND day = 28 AND caller IN ('(499) 555-9472', '(130) 555-0289', '(389) 555-5198', '(367) 555-5533');
+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       |
| 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       |
| 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
| 236 | (367) 555-5533 | (344) 555-9601 | 2021 | 7     | 28  | 120      |
| 245 | (367) 555-5533 | (022) 555-4052 | 2021 | 7     | 28  | 241      |
| 251 | (499) 555-9472 | (717) 555-1342 | 2021 | 7     | 28  | 50       |
| 285 | (367) 555-5533 | (704) 555-5790 | 2021 | 7     | 28  | 75       |
+-----+----------------+----------------+------+-------+-----+----------+

// ATM transaction from Leggett Street
sqlite> SELECT name
   ...> FROM people
   ...> JOIN bank_accounts
   ...> ON people.id = bank_accounts.person_id
   ...> JOIN atm_transactions
   ...> ON atm_transactions.account_number = bank_accounts.account_number
   ...> WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street';
+---------+
|  name   |
+---------+
| Bruce   |
| Kaelyn  |
| Diana   |
| Brooke  |
| Kenny   |
| Iman    |
| Luca    |
| Taylor  |
| Benista |
+---------+

// Where theifs fled to
SELECT *
   ...> FROM airports
   ...> WHERE id = 4;
+----+--------------+-------------------+---------------+
| id | abbreviation |     full_name     |     city      |
+----+--------------+-------------------+---------------+
| 4  | LGA          | LaGuardia Airport | New York City |
+----+--------------+-------------------+---------------+

// People that Bruce called day of robbery
SELECT name
   ...> FROM people
   ...> JOIN phone_calls
   ...> ON phone_calls.receiver = people.phone_number
   ...> WHERE month = 7 AND day = 28 AND caller = '(367) 555-5533';
+---------+
|  name   |
+---------+
| Robin   |
| Deborah |
| Gregory |
| Carl    |
+---------+
// all people on flight in the morning
sqlite> SELECT name
   ...> FROM people
   ...> JOIN passengers
   ...> ON passengers.passport_number = people.passport_number
   ...> JOIN flights
   ...> ON passengers.flight_id = flights.id
   ...> WHERE flights.month = 7 AND flights.day = 29 AND flights.id = 36;
+--------+
|  name  |
+--------+
| Doris  |
| Sofia  |
| Bruce  |
| Edward |
| Kelsey |
| Taylor |
| Kenny  |
| Luca   |
+--------+
// people Bruce called on day of robbery
SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE month = 7 AND day = 28 AND caller = '(367) 555-5533');
+-------+
| name  |
+-------+
| Robin |
+-------+