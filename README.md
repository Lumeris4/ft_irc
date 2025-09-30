# ft_irc

## Prerequisites

- **Irssi** must be installed on your system:  
  👉 [Install Irssi](https://irssi.org/download/)

- **Make** must be available on your system:  
  (Linux/macOS: usually preinstalled, Windows users can use WSL or install Make via Chocolatey or Scoop)

### 2. Launch the project

```
make
```

```./ircserv <port> <password>```

### 3. Test the project

```
irssi -n <nickname> -w <password> -p <port> -c <server>
```


### 4. bonus

## file sending

**to send a file with irssi**
```
/dcc send <nickname to send> <file>
```

**to get a file sent by someone**
```
/dcc get <nickname of sender> <file>
```


## 📜 Credits & Contributors

- 🛠️ **Lumeris4** — Developer ([GitHub](https://github.com/Lumeris4))
- 🤖 **Bfiquet** — Developer ([GitHub](https://github.com/Bfiquet))
