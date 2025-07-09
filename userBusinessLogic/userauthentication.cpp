#include "userauthentication.h"

UserAuthentication::UserAuthentication() {

    // Here we'll check for authenticaiton logic...
    // for now, we're asuming that user has been successfully authenticated

    // We'll ask this info from ui
    enteredUsername = "ram";
    enteredPass = "rampass";

    // Here we'll make a call to authenticationn api
    authenticated = callAuthenticationApi(enteredUsername, enteredPass);

}


bool UserAuthentication::callAuthenticationApi(QString &username, QString &pass) {

    if (username == "ram" &&  pass == "rampass") { // This check will happen in server. This can be done on the later stage
        return true;
    }else {
        return false;
    }
}
