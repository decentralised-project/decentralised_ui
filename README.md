Decentralised UI - Phase 1
---

Cross platform GUI client for the decentralised network. 

Phase 1 of the dc project is to establish an end to end encrypted decentralised chat platform, with public and private channels.

This repository is the main UI project, and it's dependencies are git submodules located in the /dependencies folder.

[decentralised_ui - Issue Tracker](https://github.com/decentralised-project/decentralised_ui/issues)

[decentralised_ui - Phase 1 Status](https://github.com/decentralised-project/decentralised_ui/projects/1)

### Build setup instructions

1. Download and install Qt from https://www.qt.io/
2. Clone the decentralised_ui repository resursively, to ensure all submodules are downloaded.
	
    https://github.com/decentralised-project/decentralised_ui.git
    

3. Install Perl 5 from https://www.perl.org/get.html


4. Build and install /dependencies/openssl as below:
	* Open a Visual Studio command prompt.
	* `cd` to the /dependencies/openssl directory.
	
###### Unix/Mac OSX
    
```
	$ ./config
    $ make
    $ make test    
    $ make install
```
###### Windows
    
```
    $ perl Configure { VC-WIN32 | VC-WIN64A | VC-WIN64I | VC-CE }
    $ nmake
    $ nmake test
    $ nmake install
```

5. Open QtCreator, and then the decentralised_ui project, and all the projects in the /dependencies folder.


6. Run qmake on all the projects.


7. Build all the dependencies projects.


8. Build and run the decentralised_ui project.