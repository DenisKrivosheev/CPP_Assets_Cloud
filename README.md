# CPP_Assets_Cloud



## In Visual Studio
Using HttpLib hfile, more at https://github.com/yhirose/cpp-httplib 
In source files add httplib.h file
Follow these steps to set the working directory in Visual Studio:

Right-click on your project in the Solution Explorer, and select "Properties."

In the properties window, navigate to the "Configuration Properties" > "Debugging" section.

In the "Working Directory" field, enter the full path to the folder containing your images. In this case, it will be the path to the "imgs" folder. You can use the "$(ProjectDir)" macro to represent the project's directory.

For example, if your project is located in "C:\Users\YourUserName\Projects\MyProject," and the images are in "C:\Users\YourUserName\Projects\MyProject\imgs," you would set the "Working Directory" as "$(ProjectDir)imgs."

Save the changes and rebuild your project.