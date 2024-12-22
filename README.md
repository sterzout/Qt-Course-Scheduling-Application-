**Course Scheduling Application**
**Description**
-This project is a course and user management system designed to streamline the administration of courses and student information. It allows for adding, removing, and managing courses and users, as well as displaying notifications and maintaining data consistency using file operations. The system implements key Object-Oriented Design (OOD) principles and utilizes design patterns like Singleton and Proxy to ensure scalability and maintainability.

**Features** 
- Add, remove, and manage courses.
- Manage students and see student account information through admin.
- Notifications for actions like course additions and removals.
- Comprehensive GUI using the Qt framework.

**Dependencies**
- To compile and run this project you will need the following:
- Qt Framework (I made sure to use 6.0 or higher)
- C++ Compiler (C++ 17 worked for me)
- Google Test and Google Mock (Optional, for unit testing)

**File Paths**
The system reads and writes data to text files (courses.txt, userlogininfo.txt, etc.) I tried to do absolute dir through Qt but the most certain way this will work is to replace all instances where the text reads up to the txt name with the file path found on your local computer. Use "replace all" and this can be done in 3 clicks. Ex: /Users/sterzout/Documents/... will be substituted with the absolute path to the text files on your device.

**Compilation and Setup Instructions**
- Download and install Qt: Install the Qt framework from Qt downloads.
- Ensure that the Qt creator IDE is configured with a compatible compiler.
- Open the Project: Open Qt Creator. -Navigate to File -> Open File or Project and select the .pro file, configure the project by selecting a build configuration (e.g., Debug or Release).
- If no executable is selected or you are not prompted to pick one, simply go to Projects -> Build & Run -> Add Kit and select a valid kit.

![Screenshot 2024-12-20 at 10 10 47 PM](https://github.com/user-attachments/assets/a6f81ca7-5dfc-45c7-9256-295b9445a0ec)


- Click on the "Run" button or navigate to Build -> Run to compile and execute the program. Run the Executable:
