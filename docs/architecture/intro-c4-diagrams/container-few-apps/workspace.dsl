workspace {
    model {
        terminal = softwareSystem "Harvester Terminal" {
            tags "Focus"
            description "Yield optimisation, customer accounting"

            windowAppMgr = container "Window & App Manager" {
                tags "SingleApp"
                technology "Wayland"
            }
            terminalApp = container "Terminal App" {
                tags "Focus" "SingleApp"
                technology "QML, Qt, C++"
            }
            vncServer = container "VNC Server" {
                technology "RealVNC"
            }
            j1939Service = container "J1939 Service" {
                technology "Qt Can Bus, C++"
            }
            iotClient = container "IoT Client" {
                technology "Qt MQTT, C++"
            }
            updateApp = container "Update App" {
                technology "QML, Qt, C++"
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

        # Relationships on context level
        driver -> terminal "Uses"
        iotCloud -> terminal "Installs updates" "HTTPS"
        terminal -> iotCloud "Logs machine data" "MQTT over LTE-M"
        terminal -> harvesterEcus "Reads/writes ECU parameters" "J1939 over CAN"
        harvesterCams -> terminal "Sends video frames" "Ethernet: 100 Mbps"
        operatingConditions -> terminal "Impacts"

        # Relationships between TerminalContext and terminal applications (single app)
        windowAppMgr -> terminalApp "Shows/hides" "Wayland"
        driver -> windowAppMgr "Uses"
        operatingConditions -> windowAppMgr "Impacts"
        harvesterCams -> terminalApp "Sends video frames" "Ethernet: 100 Mbps"
        iotCloud -> terminalApp "Installs updates" "HTTPS" {
           tags "SingleApp"
        }
        terminalApp -> iotCloud "Logs machine data" "MQTT over LTE-M" {
            tags "SingleApp"
        }
        terminalApp -> harvesterEcus "Reads/writes ECU parameters" "J1939 over CAN" {
           tags "SingleApp"
        }

        # Relationships between TerminalContext and terminal applications (few apps)
        windowAppMgr -> vncServer "Sends display frames" "Wayland"
        vncServer -> iotCloud "Mirror display frames" "VNC over LTE-M"

        windowAppMgr -> j1939Service "Starts/stops" "Qt Remote Objects"
        terminalApp -> j1939Service "Sends/receives machine data" "Qt Remote Objects"
        j1939Service -> harvesterEcus "Reads/writes ECU parameters" "J1939 over CAN"

        windowAppMgr -> iotClient "Starts/stops" "Qt Remote Objects"
        iotClient -> j1939Service "Sends/receives machine data" "Qt Remote Objects"
        iotClient -> iotCloud "Logs machine data" "MQTT over LTE-M"

        windowAppMgr -> updateApp "Shows/hides" "Wayland"
        updateApp -> j1939Service "Sends/receives machine data" "Qt Remote Objects"
        iotCloud -> updateApp "Installs updates" "HTTPS"
    }

    views {
        systemContext terminal TerminalContext {
            include *
            autoLayout lr
        }

        container terminal ContainerSingleApp {
            include "element.tag==SingleApp"
            include "element.tag==TerminalContext"
            autoLayout lr
        }

        container terminal ContainerFewApps {
            include *
            include "element.tag==TerminalContext"
            exclude "relationship.tag==SingleApp"
            autoLayout lr
        }

        # Styling
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
