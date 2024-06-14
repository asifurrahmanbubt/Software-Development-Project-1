# Calendar Program in C

## Overview

This project is a calendar program written in C that allows users to initialize a month, add tasks to specific days, modify or delete tasks, view tasks, save tasks to a file, load tasks from a file, and search for tasks by description.

## Features

- **Initialize a Month:** Calculate the number of days and the starting day of the week for any given month of any year.
- **Print the Calendar:** Display the calendar for a specified month, showing the days of the week.
- **Add, Modify, Delete Tasks:** Manage tasks for specific days within the month.
- **View Tasks:** View tasks for a specific day and provide options to modify, delete, or change the date of tasks.
- **Save and Load Tasks:** Save tasks to a file and load tasks from a file for persistent storage.
- **Search Tasks:** Search for tasks by description and provide options to manage the found tasks.

## How to Use

1. **Initialize a Month:**
   - The program prompts for the year and month.
   - It calculates the number of days and the starting day of the week for the month.

2. **Print the Calendar:**
   - The calendar for the specified month is displayed with days of the week.

3. **Add Tasks:**
   - The program prompts for the day and task description.
   - Tasks can be added to specific days of the month.

4. **View and Manage Tasks:**
   - View tasks for a specific day.
   - Modify, delete, or change the date of tasks.

5. **Save Tasks:**
   - Save tasks to a file by providing a filename.
   - The tasks for the month are written to the specified file.

6. **Load Tasks:**
   - Load tasks from a file by providing a filename.
   - The tasks are read from the file and displayed in the calendar.

7. **Search Tasks:**
   - Search for tasks by description.
   - Manage the found tasks by modifying, deleting, or changing their date.

## Code Explanation

### Main Components

- **Struct `Month`:** Represents a month with attributes for year, month, number of days, starting day, and tasks.
- **Function `is_leap_year`:** Determines if a given year is a leap year.
- **Function `init_month`:** Initializes a month with year, month, number of days, and starting day.
- **Function `print_month`:** Prints the calendar for the month.
- **Function `add_task`:** Adds a task to a specific day.
- **Function `modify_task`:** Modifies an existing task on a specific day.
- **Function `delete_task`:** Deletes a task from a specific day.
- **Function `view_tasks`:** Views tasks for a specific day and provides options to manage them.
- **Function `save_tasks`:** Saves tasks to a file.
- **Function `load_tasks`:** Loads tasks from a file.
- **Function `search_tasks`:** Searches for tasks by description and provides options to manage them.

## Project Details

- **Course:** Software Development Project 1
- **Project Title:** Create a Calendar Program using C Programming Language
- **Project Supervisor:** MD Ashraful Islam, Assistant Professor, Department of Computer Science & Engineering, Bangladesh University of Business and Technology.

### Project Members

- Asifur Rahman (ID: 22234103353)
- Ferdouse Hassan Nowrin (ID: 22234103237)
- TASNIMUL HAQUE NAHIN (ID: 22234103180)
- Mahajabin Kabir Arin (ID: 22234103213)
- Delwar Hossain Roman (ID: 22234103233)
