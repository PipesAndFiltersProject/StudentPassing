# Installed files

This directory contains files which should be installed with the BasicInfoGUI binary to the computer where the node is executed. If the computer runs only one node, only the corresponding data and configuration files should be installed. If you run all the nodes in the same computer, install all the data and configuration files.

Node expects to find a directory named *StudentPassing* in the *home directory* of the user running the Node app. So *copy* the StudentPassing directory into the user's home directory, with the configuration and data files. You may then edit the files in that directory, according to your preferences, and remove unnecessary files from the computer if you run only one node on the computer.

Note that the node configuration files contain paths to the datafiles the nodes use. These paths **do not work** in your computer before you edit the paths to work in your computer. So when you have copied the StudentPassing to  your user home directory, open each configuration file and **edit the paths** to fit your environment.

The nodes are configured the following way:

* **BasicInfoConfig.txt** configures the *first* node in the architecture. It has no incoming data from the network, it has a data file user can edit to enter basic student information. User can also enter new student data from the GUI. Note that in the data and configuration files, *tabs* are used to separate items in a line. Edit the outgoing IP address with port according to the configuration of the next node in the architecture. See the configuration file to see how the node is configured. The data entered or read from the file will be send as a JSON message package to the next node.
* **ExerciseInfoConfig.txt** configures the *second* node in the architecture. It received incoming student data as JSON in UDP packets from the first node. Again user is able to read data from a tab separated data file, and enter exercise points from the GUI (separate exercise points for several exercises with comma in the GUI textbox). Data received from the previous node and the data entered through the GUI/data file is then *combined* by the node, and this aggredated data is then sent as a JSON package to the next node.
* **ExamInfoConfig.txt** configures the *third* node in the architecture. Users can enter points from examinations in this node. There is only one examination so one integer number should be entered in the GUI. As with previous nodes, also a data file is provided to read several exam points for several students at one go. Again the node combines this new course passing data with the data received from the previous node, and when aggregated data is ready, it is then sent to the next node in the architecture.
* The configuration for the *final, fourth* node is **ProjectInfoConfig.txt**. In this node, course project points are combined with the data received from the previous node. As a final node in the architecture, this node also calculates the grade for the student, based on the aggregated data produced by this and all the previous nodes in the architecture. Since this is the final node, it doesn not send the aggregated data anywhere, but writes the grading and student data into a text file, which can be then evaluated by the course teacher and sent forward to the faculty study secretaries. In the future, integration to the University system could be developed, to automatically enter the course passing data to the system without human intervention.

How can you make sure which is the right order of the nodes? By checking the addresses the nodes receive from and send to their data, in the configuration files. 
How to know the IP addressses of the machines you are using? In Linux and macOS, use the command ifconfig, which lists the addresses and network interfaces of the device. From there, you should be able to find the address. In Windows, use the ipconfig command, or see the network settings from the Control Panel.

Study the contents of the configuration and data files. If you decide to run the nodes on a single computer to study the behaviour, you need to only change the data file paths in the configuration files. If you want to test how nodes can be executed on different computers (on the same network!), you then need to check the IP addresses of the computers and edit the node configuration files to make sure nodes do know where they should be sending their packages.

You configure the node by starting the node with the cofiguration file as the startup parameter of the node (on Linux and Mac):

    ./BasicInfoGUI ExerciseInfoConfig

Note that you must not give the file extension in the parameter, just the name without the extension. If the node does not start, then the configuration file does not exist or some other problem prevents reading it. See the log files (below) to find out what the problem is.

The StudentPassing directory also contains a Logs directory. This is where the node(s) will store the logging files they produce. Study the logs to gain further undestanding on how the system works. Obviously they can also be studied if there are any problems with running the system.

When you run the nodes and provide input to them, using the data files and/or GUI, you should then be able to see student grading information saved in the last node's output data file. See the configuration file ProjectInfoConfig.txt to see what is the name and location of the output file produced. Please note that no data is written to that file until *all* nodes have provided the points needed to calculate the grade for a student. Students are identified by the student number, so on each node, user has to enter data for that same student id in order to have actual grading data for that student in the output file.

