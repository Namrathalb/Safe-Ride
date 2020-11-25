#include "MyWebEnginePage.h"


bool MyWebEnginePage::acceptNavigationRequest(const QUrl &url, QWebEnginePage::NavigationType type, bool isMainFrame)
{
    if (type == QWebEnginePage::NavigationTypeLinkClicked)
    {
        // retrieve the url here
        qDebug() << Q_FUNC_INFO <<"Start "<<type<< "url" <<url.toString()<< endl;
        emit linkClicked(url);
        return false;
    }

    return true;
}
