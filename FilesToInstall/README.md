# Files to install

This directory contains files which should be installed with the StudentPassing gui binary (and the libraries used) to the computer where the Node is executed. 

If the computer runs only one Node, only the corresponding data and configuration files should be installed. If you run all the Nodes in the same computer, install all the data and configuration files.

Node expects to find a directory named **StudentPassing** in the **home directory** of the user running the Node app. **Copy** the StudentPassing directory into the user's home directory, with the configuration and data files. 

You may then **edit** the files in that directory, according to your preferences, and remove unnecessary files from the computer if you run only one Node on the computer.

Note that the Node configuration files contain paths to the datafiles the Nodes use. These paths **do not work** in your computer before you edit the paths to work in your computer. So when you have copied the StudentPassing to  your user home directory, open each configuration file and **edit the paths** to fit your environment.

Also, **change the IP addresses** of the Nodes data packages are sent to from each Node. IP addresses change when you use different networks. Also, DHCP may give your machine different IP addresses when you reconnect to that network. Host name resolving should be used to find hosts based on names, but this has not yet been implemented.

The **file structure** of data and configuration files are similar. First line always describes the content type of the file. The following lines are lines containing one data item each as [tab separated values](https://en.wikipedia.org/wiki/Tab-separated_values).

The Nodes are configured the following way:

* **BasicInfoConfig.txt** configures the *first* Node in the architecture. 
    * It has a data file user can edit to enter basic student information. User can also enter new student data from the GUI.
    * Edit the outgoing IP address with port according to the configuration of the *next Node* in the architecture. See the configuration file of the next Node to see how the Node is configured.
* **ExerciseInfoConfig.txt** configures the *second* Node in the architecture. 
    * It received incoming student data from the first Node.
    * Again user is able to read data from a tab separated data file, and enter exercise points from the GUI (separate exercise points for several exercises with comma in the GUI textbox). 
    * Data received from the previous Node and the data entered through the GUI/data file is then *combined* by the Node, and this aggredated data is then sent as a JSON package to the next Node.
* **ExamInfoConfig.txt** configures the *third* Node in the architecture.
    * Users can enter points from examinations in this Node. There is only one examination so one integer number should be entered in the GUI. 
    * As with previous Nodes, also a data file is provided to read several exam points for several students at one go. Again the Node combines this new course passing data with the data received from the previous Node, and when aggregated data is ready, it is then sent to the next Node in the architecture.
* The configuration for the *final, fourth* Node is **ProjectInfoConfig.txt**. 
    * In this Node, course project points are combined with the data received from the previous Node. 
    * As a final Node in the architecture, this Node also calculates the grade for the student, based on the aggregated data produced by this and all the previous Nodes in the architecture. Since this is the final Node, it doesn not send the aggregated data anywhere, but writes the grading and student data into a text file, which can be then evaluated by the course teacher and sent forward to the faculty study secretaries. 
    * In the future, integration to the University system could be developed, to automatically enter the course passing data to the system without human intervention.

How can you make sure which is the right order of the Nodes? By checking the IPaddresses the Nodes receive from and send to their data, in the configuration files. 

How to know the IP addressses of the machines you are using? In Linux and macOS, use the command `ifconfig`, which lists the addresses and network interfaces of the device. From there, you should be able to find the address. In Windows, use the `ipconfig` command, or see the network settings from the Control Panel.

Study the contents of the configuration and data files. If you decide to run the Nodes on a single computer to study the behaviour, you need to only change the IP addresses to the machine's IP address and data file paths in the configuration files. 

If you want to test how Nodes can be executed on different computers (on the same local network), you then need to check the IP addresses of the computers and edit the Node configuration files to make sure Nodes do know where they should be sending their packages.

You configure the Node by starting the Node with the cofiguration file as the startup parameter of the Node (on Linux and Mac):

    ./spgui ExerciseInfoConfig

Note that you *should not* give the file extension nor path to the StudentPassing directory in the parameter, just the configuation file name without the extension. If the Node does not start, then the configuration file does not exist in the <*user home*>/StudentPassing directory, or some other problem prevents reading it. See the log files (below) to find out what the problem is.

The StudentPassing directory also must contain a Logs directory *you need to create*. This is where the Node(s) will store the logging files. When copying the StudentPassing directory to your user home directory, also create the subdirectory StudentPassing/Logs. Study the logs to gain further undestanding on how the system works. Obviously they can also be studied if there are any problems with running the system.

When you run the Nodes and provide input to them, using the data files and/or GUI, you should then be able to see student grading information saved in the last Node's output data file. See the configuration file `ProjectInfoConfig.txt` to see what is the name and location of the output file produced. 

Please note that data is written to that file for a single student when *all* Nodes have provided the points needed to calculate the grade for that student. Students are identified by the student number, so on each Node, user has to enter data for that same student id in order to have actual grading data for that student in the output file.

