
class VolumeSelector {
public:
    enum VolumeLevel {
        EXTRA_QUIET,
        QUIET,
        NORMAL,
        LOUD,
        EXTRA_LOUD
    };

    VolumeSelector(int pinWithResistor, int pinNoResistor);
    void SetLevel(VolumeLevel vol);

protected:
    int pinWithResistor;
    int pinNoResistor;
};
