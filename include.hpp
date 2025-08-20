#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>      // types de base (souvent inclus par d'autres)
#include <sys/socket.h>     // pour socket(), bind(), listen(), accept(), etc.
#include <netinet/in.h>     // pour struct sockaddr_in et constantes AF_INET, htons(), INADDR_ANY
#include <arpa/inet.h> 
#include <cstdlib>
#include <netdb.h>
#include <unistd.h>
#include <netdb.h>
#include <cstdio>
#include <sstream>
#include <cstdlib>
#include <errno.h>
#include <string.h>
#include <poll.h>
#include <vector>
#include <map>
#include <algorithm>
#include <signal.h>