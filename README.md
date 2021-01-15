# SharedDeliveryCost-CSE201Project

The SharedDeliveryCost web application will allow users to get connected with other users in order to make a group delivery from a company, by that decreasing the delivery costs they need to pay.

The application allows you to:

1. Register and log in as a user. Giving the following information:
   - email address (used for log in and future contacting)
   - password
   - Name and Surname (username)
   - Default location
2. Make an order by giving the following informations:
   - company the user wants to order from (ex. Ikea)
   - amount of his order
   - how much he is willing to pay for the shipping cost
   - location (if different from him default one)
   - distance willing to go to pick up his order (ex. None- for big objects, 500m for something small)
3. Recieve a notification when their order has been grouped. This contains:
   - The contact information of the people you were grouped in order to share your delivery
   - The portion of the delivery you are going to pay
   - An address for the delivery taking into account the "locations" and "willingness to go" from all included parties

## Members (name surname, github username, trello username, [role])

- Gorazd Dimitrov, gogodim, gorazddimitrov, Project leader
- Maika Edberg, maikaedberg, maikaedberg, Localiation leader
- Sigurjon Agustsson, SigurjonAg, sigurjonagustsson, Databases and server leader
- Danaé Broustail, danaebroustail, danaebroustail, Back-end leader
- Yarou Hsu, yarou1025, yarou1025, Trello leader
- Leonardo Israilovici, leoisrailovici, leonardoisrailovici, Optimization leader
- Estelle Martin, estellemartin, estellemartin20, Git leader

## Running the project

### Prerequisites
- WT library (installation guide for Windows provided)
- OpenSSL installed and added to path on machine
- Boost library bundle installed

### Other set-ups, building and running
1. Command line arguments

In order to be able to run first adjuce the command line arguments in the QT project by modifying the following line:
```
--docroot="path_to_project\\SharedDeliveryCost-CSE201Project\\SDC\\SDC" --http-port=9090 --http-address=0.0.0.0 ---config wt_config.xml --resources-dir="path_to_the_parent_directory_of_project"
```
2. Clearing old Database

Delete the "SDB.db" file from "SharedDeliveryCost-CSE201Project/SDC/SDC" in order for the system to create it by itself at the first running of the project on a new machine.

3. Compiler

Make sure you are using the right compiler, initially the libraries are set for 64-bit compiler, if using a 32-bit machine be careful to change it in the SDC.pro file as well as in the Qt configuration.

4. Build and run the project directly from Qt.

#### Warning

The project contains a big part of CSS ("resources" folder in "SDC/SDC") which is not written by the students, but comes with the Wt library, and is subject to copyright. This folder is present on the repository to easen the process of running the project and avoid complications that mey occure if one must link the resources from the command line arguments.
