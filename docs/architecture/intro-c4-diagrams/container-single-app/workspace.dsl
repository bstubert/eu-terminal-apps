workspace {
    model {
        terminal = softwareSystem "Harvester Terminal" {
            tags "Focus"
            description "Yield optimisation, customer accounting"

            windowAppMgr = container "Window & App Manager" {
                technology "Wayland"
            }
            terminalApp = container "Terminal App" {
                tags "Focus"
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

        # Relationships between TerminalContext and terminal applications
        windowAppMgr -> terminalApp "Shows/hides" "Wayland"
        driver -> windowAppMgr "Uses"
        operatingConditions -> windowAppMgr "Impacts"
        harvesterCams -> terminalApp "Sends video frames" "Ethernet: 100 Mbps"
        iotCloud -> terminalApp "Installs updates" "HTTPS"
        terminalApp -> iotCloud "Logs machine data" "MQTT over LTE-M"
        terminalApp -> harvesterEcus "Reads/writes ECU parameters" "J1939 over CAN"
    }

    views {
        systemContext terminal TerminalContext {
            include *
            autoLayout lr
        }

        container terminal ContainerSingleApp {
            include *
            include "element.tag==TerminalContext"
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
