workspace {

    model {
        person1 = person "<Person Name>" "<Description>"

        system1 = softwareSystem "<System Name 1>" "<Description>" {
            container1 = container "<Container Name 1>" "<Description>" "<Technology>" {
                component1 = component "<Component Name 1>" "<Description>" "<Technology>"
                component2 = component "<Component Name 2>" "<Description>" "<Technology>"
            }
            container2 = container "<Container Name 2>" "<Description>" "<Technology>"
        }
        
        system2 = softwareSystem "<System Name 2>" "<Description>"
        
        person1 -> system1 "<Description>" "<Technology>"
        system1 -> system2 "<Description>" "<Technology>"

        container1 -> container2 "<Description> "<Technology>"

        component1 -> component2 "<Description> "<Technology>"
    }

    views {
        systemContext system1 "LegendContext" {
            include *
            autoLayout lr
        }
        
        container system1 "LegendContainer" {
            include *
            autoLayout lr
        }
        
        component container1 "LegendComponent" {
            include *
            autoLayout lr
        }
        
        theme default
    }
}

