# Safe-Ride-accelrometer

# Problem Statement
Humps and pit holes on a road have been present from the day road was made into existence. It has been one of the major problems in the maintenance of roads. Due to this many accidents and vehicle damages have been occurring especially in a metropolitan city where vehicles are more. 

# Solution

A solution to this problem is to develop a system which captures the geographical location coordinates of the potholes and humps using a global positioning system receiver. Accelerometer sensors are used to identify the pit holes and humps and also to measure their depth, width and height, respectively. The sensed-data includes geographic location, which is stored in the database (cloud) for a particular road. so that the next Driver on the same road would have a pre-data about the road where humps and pit holes are recorded and can be used to give Voice notification to the driver within a given range say 100m away from it by keeping track of his GPS location.



hello i have question

i have webpage opened with Qwebengine view

now there are links in that webpage so when i double click or cick the link i want it to open in a new dialog.ui which has qwebengine view

like in maindow page i have

ui->view->load(str);

that has some links in the site i am using modeless approach to open new dialog when the link is triggered.

QAction* openInNewTab = ui->view->pageAction(QWebEnginePage::OpenLinkInNewTab);
connect(openInNewTab, SIGNAL(triggered()), this, SLOT(on_actionNewTab_triggered()));

it opens a empty dialog even i though i have defined on_actionnewtab_trigger()

QObject *senderObj = sender();
QString readnews = senderObj->objectName();
d = new Dialog ();
d->show();
d->read(readnews);

where am i doing wrong???
