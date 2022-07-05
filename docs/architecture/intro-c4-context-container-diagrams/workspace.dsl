workspace {

    model {
        terminal = softwareSystem "Harvester Terminal" {
            tags "Focus"
            description "Yield optimisation, customer accounting"
            
            windowAppMgr = container "Window & App Manager" "" "Wayland" {
                tags "SingleApp" "FewApps" "ManyApps"            
            }
            terminalApp = container "Terminal App" "" "QML, Qt, C++" {
                tags "SingleApp" "FewApps" "ManyApps" "Focus"      
            }

            updateApp = container "Update App" "" "QML, Qt, C++" {
                tags "FewApps" "ManyApps"       
            }
            vncServer = container "VNC Server" "" "Qt, C++" {
                tags "FewApps" "ManyApps"            
            }
            iotClient = container "IoT Client" "" "Qt, C++" {
                tags "FewApps" "ManyApps"            
            }
            j1939Service = container "J1939 Service" "" "Qt, C++" {
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
            
            moreApps = container "App 1...N" "" "QML, Qt, C++" {
                tags "ManyApps"
            }
           
            windowAppMgr -> terminalApp "Shows/hides" "Wayland" {
               tags "SingleApp" "FewApps" "ManyApps"
            }
            windowAppMgr -> cameraApp "Shows/hides" "Wayland" {
               tags "ManyApps"
            }
            windowAppMgr -> diagnosisApp "Shows/hides" "Wayland" {
               tags "ManyApps"
            }
            windowAppMgr -> calibrationApp "Shows/hides" "Wayland" {
               tags "ManyApps"
            }
            windowAppMgr -> updateApp "Shows/hides" "Wayland" {
               tags "FewApps" "ManyApps"
            }
            windowAppMgr -> moreApps "Shows/hides" "Wayland" {
               tags "ManyApps"
            }
            windowAppMgr -> vncServer "Sends display frames" "Wayland" {
               tags "FewApps" "ManyApps"
            }
            windowAppMgr -> vncServer "Starts/stops" "Qt Remote Objects" {
               tags "FewApps" "ManyApps"
            }
            windowAppMgr -> iotClient "Starts/stops" "Qt Remote Objects" {
               tags "FewApps" "ManyApps"
            }
            windowAppMgr -> j1939Service "Starts/stops" "Qt Remote Objects" {
               tags "FewApps" "ManyApps"
            }
            terminalApp -> j1939Service "Sends/receives machine data" "Qt Remote Objects" {
               tags "FewApps" "ManyApps"
            }
            updateApp -> j1939Service "Sends/receives machine data" "Qt Remote Objects" {
               tags "FewApps" "ManyApps"
            }
            iotClient -> j1939Service "Sends/receives machine data" "Qt Remote Objects" {
               tags "FewApps" "ManyApps"
            }           
            cameraApp -> j1939Service "Sends/receives machine data" "Qt Remote Objects" {
               tags "ManyApps"
            }
            diagnosisApp -> j1939Service "Sends/receives machine data" "Qt Remote Objects" {
               tags "ManyApps"
            }
            calibrationApp -> j1939Service "Sends/receives machine data" "Qt Remote Objects" {
               tags "ManyApps"
            }
            moreApps -> j1939Service "Sends/receives machine data" "Qt Remote Objects" {
               tags "ManyApps"
            }
        }
        driver = person "Driver" {
            tags "TerminalContext"
            description "Drives sugar-beet harvester"
        }
        iotCloud = softwareSystem "IoT Cloud" {
            tags "TerminalContext"
            description "Monitoring harvesters, OTA updates, remote support"
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
        
        driver -> windowAppMgr "Uses" {
            tags "SingleApp" "FewApps" "ManyApps"
        }
        iotClient -> iotCloud "Logs machine data" "MQTT over LTE-M" {
            tags "FewApps" "ManyApps"
        }
        vncServer -> iotCloud "Mirror display frames" "VNC over LTE-M" {
            tags "FewApps" "ManyApps"
        }
        iotCloud -> updateApp "Installs updates" "HTTPS" {
            tags "FewApps" "ManyApps"
        }
        iotCloud -> terminalApp "Installs updates" "HTTPS" {
            tags "SingleApp"
        }
        harvesterCams -> terminalApp "Sends video frames" "Ethernet: 100 Mbps" {
            tags "SingleApp" "FewApps"
        }
        harvesterCams -> cameraApp "Sends video frames" "Ethernet: 100 Mbps" {
            tags "ManyApps"
        }
        j1939Service -> harvesterEcus "Reads/writes ECU parameters" "J1939 over CAN" {
            tags "SingleApp" "FewApps" "ManyApps"
        }
        terminalApp -> harvesterEcus "Reads/writes ECU parameters" "J1939 over CAN" {
            tags "SingleApp"
        }
        operatingConditions -> windowAppMgr "Impacts" {
            tags "SingleApp" "FewApps" "ManyApps"
        }
    }

    views {
        systemContext terminal "HarvesterTerminalContextDiagram" {
            include *
            autoLayout lr
        }
                
        container terminal "ContainerSingleApp" {
            include "element.tag==SingleApp" 
            include "element.tag==TerminalContext"
            autoLayout lr
        }

        container terminal "ContainerFewApps" {
            include "element.tag==FewApps"
            include "element.tag==TerminalContext"
            exclude "relationship.tag!=FewApps"
            autoLayout lr
        }

        container terminal "ContainerAllApps" {
            include "element.tag==ManyApps" 
            include "element.tag==TerminalContext"
            exclude "relationship.tag!=ManyApps"
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
