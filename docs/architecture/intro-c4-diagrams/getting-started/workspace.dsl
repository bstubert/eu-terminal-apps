workspace {

    model {
        terminal = softwareSystem "Harvester Terminal" 
        driver = person "Driver" 

        driver -> terminal "Uses"
    }

    views {
        systemContext terminal TerminalContext {
            include *
            autoLayout lr
        }
        
        theme default
    }
}
