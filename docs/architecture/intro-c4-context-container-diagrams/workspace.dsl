workspace {

    model {
        terminal = softwareSystem "Harvester Terminal" {
            tags "Focus"
            description "Yield optimisation, customer accounting"
            
            windowAppMgr = container "Window & App Manager" "" "QML, Qt, C++" {
                tags "SingleApp" "FewApps" "ManyApps"            
            }
            terminalApp = container "Terminal App" "" "QML, Qt, C++" {
                tags "SingleApp" "FewApps" "ManyApps" "Focus"      
            }

            updateApp = container "Update App" "" "QML, Qt, C++" {
                tags "FewApps" "ManyApps"            
            }
            vncServer = container "VNC Server" "Qt, C++" {
                tags "FewApps" "ManyApps"            
            }
            iotClient = container "IoT Client" "Qt, C++" {
                tags "FewApps" "ManyApps"            
            }
            j1939Service = container "J1939 Service" "Qt, C++" {
                tags "FewApps" "ManyApps"            
            }
            
            cameraApp = container "Camera App" "" "QML, Qt, C++" {
                tags "ManyApps"
            }
            
            diagnosisApp = container "Diagnosis App" "" "QML, Qt, C++" {
                tags "ManyApps"
            }
            
            calibrationApp = container "Calibration App" "" "QML, Qt, C++" {
                tags "ManyApps"
            }
           
            windowAppMgr -> terminalApp "Shows/hides" "Wayland"
            windowAppMgr -> cameraApp "Shows/hides" "Wayland"
            windowAppMgr -> diagnosisApp "Shows/hides" "Wayland"
            windowAppMgr -> calibrationApp "Shows/hides" "Wayland"
            windowAppMgr -> diagnosisApp "Shows/hides" "Wayland"
            windowAppMgr -> updateApp "Shows/hides" "Wayland"
            windowAppMgr -> vncServer "Sends display frames" "Wayland"
            terminalApp -> j1939Service "Sends/receives machine data" "Qt Remote Objects"
            terminalApp -> iotClient "Starts/stops" "Qt Remote Objects"
            terminalApp -> vncServer "Starts/stops" "Qt Remote Objects"
            updateApp -> j1939Service "Sends/receives machine data" "Qt Remote Objects"
            iotClient -> j1939Service "Sends/receives machine data" "Qt Remote Objects"           
            cameraApp -> j1939Service "Sends/receives machine data" "Qt Remote Objects"
            diagnosisApp -> j1939Service "Sends/receives machine data" "Qt Remote Objects"
            calibrationApp -> j1939Service "Sends/receives machine data" "Qt Remote Objects"
        }
        driver = person "Driver" {
            tags "TerminalContext"
            description "Drives sugar-beet harvester"
        }
        iotCloud = softwareSystem "IoT Cloud" {
            tags "TerminalContext"
            description "Monitoring harvesters, OTA updates"
        }
        harvesterEcus = softwareSystem "Harvester ECUs" {
            tags "TerminalContext"
            description "Controlling header, engine, conveyor belts, bunker"
        }
        operatingConditions = element "Operating Conditions" "Constraint" {
            tags "Constraint" "TerminalContext"
            description "Temperature, light, dust, water, vibration"
        }
        harvesterCams = softwareSystem "Harvester Cameras" {
            tags "TerminalContext"
            description "Rear-view, turbine, bunker and header cameras"
        }

        driver -> terminal "Uses"
        iotCloud -> terminal "Installs updates" "HTTPS"
        terminal -> iotCloud "Logs machine data" "MQTT over LTE-M"
        terminal -> harvesterEcus "Reads/writes ECU parameters" "J1939 over CAN"
        harvesterCams -> terminal "Sends video frames" "Ethernet: 100 Mbps"
        operatingConditions -> terminal "Impacts"
        
        driver -> windowAppMgr "Uses"
        iotClient -> iotCloud "Logs machine data" "MQTT over LTE-M"
        iotCloud -> updateApp "Installs updates" "HTTPS"
        iotCloud -> terminalApp "Installs updates" "HTTPS" {
            tags "SingleApp"
        }
        harvesterCams -> terminalApp "Sends video frames" "Ethernet: 100 Mbps" {
            tags "SingleApp" "FewApps"
        }
        harvesterCams -> cameraApp "Sends video frames" "Ethernet: 100 Mbps"
        j1939Service -> harvesterEcus "Reads/writes ECU parameters" "J1939 over CAN"
        terminalApp -> harvesterEcus "Reads/writes ECU parameters" "J1939 over CAN" {
            tags "SingleApp"
        }
        operatingConditions -> windowAppMgr "Impacts"
    }

    views {
        systemContext terminal "HarvesterTerminalContextDiagram" {
            include *
            autoLayout lr
        }
                
        container terminal "ContainerSingleApp" {
            include "element.tag==SingleApp" "element.tag==TerminalContext"
            autoLayout lr
        }

        container terminal "ContainerFewApps" {
            include "element.tag==FewApps" "element.tag==TerminalContext"
            autoLayout lr
        }

        container terminal "ContainerAllApps" {
            include *
            exclude "relationship.tag==SingleApp"  "relationship.tag==FewApps"
            autoLayout lr
        }
       
        styles {
            element "Constraint" {
                shape Circle
                background #393645
                color #ffffff
            }
            element "Focus" {
                background #ff0000
            }
        }
        
        theme default
    }

}
