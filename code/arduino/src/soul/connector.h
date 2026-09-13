#ifndef connector_h
#define connector_h

/**
 * @brief Abstract base class for robot communication channels (Serial, Web, Bluetooth, etc.).
 *
 * Connectors ingest remote commands from clients and update the central Mind state.
 */
class Connector {
  public:
    virtual ~Connector() {}
    virtual void init() = 0;
    virtual void handleConnection() = 0;
};

#endif
