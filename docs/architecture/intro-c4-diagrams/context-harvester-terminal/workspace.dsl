workspace {

    model {
        terminal = softwareSystem "Harvester Terminal" {
            tags "Focus"
            description "Yield optimisation, customer accounting"
        }
        driver = person "Driver" {
            description "Drives sugar-beet harvester"
        }
        iotCloud = softwareSystem "IoT Cloud" {
            description "Monitoring harvesters, OTA updates, remote support"
        }
        harvesterEcus = softwareSystem "Harvester ECUs" {
            tags "TerminalContext"
            description "Controlling header, engine, conveyor belts, bunker"
        }
        harvesterCams = softwareSystem "Harvester Cameras" {
            description "Rear-view, turbine, bunker and header cameras"
        }
        operatingConditions = element "Operating Conditions" "Constraint" {
            tags "Constraint"
            description "Temperature, light, dust, water, vibration"
        }

        driver -> terminal "Uses"
        iotCloud -> terminal "Installs updates" "HTTPS"
        terminal -> iotCloud "Logs machine data" "MQTT over LTE-M"
        terminal -> harvesterEcus "Reads/writes ECU parameters" "J1939 over CAN"
        harvesterCams -> terminal "Sends video frames" "Ethernet: 100 Mbps"
        operatingConditions -> terminal "Impacts"
    }

    views {
        systemContext terminal TerminalContext {
            include *
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
