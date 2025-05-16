class EmbeddedClass {
private:
    uint8_t attribute1;
    bool attribute2;

public:
    EmbeddedClass(uint8_t initialValue) : attribute1(0U), attribute2(false) {
        if (initialValue <= 100U) {
            attribute1 = initialValue;
        } else {
            attribute2 = true;
        }
    }

    ~EmbeddedClass() {
        attribute1 = 0U;
        attribute2 = false;
    }

    void initialize(void) {
        attribute1 = 0U;
        attribute2 = false;
    }

    void update(void) {
        if (attribute1 < 255U) {
            attribute1++;
        } else {
            attribute2 = true;
        }
    }

    uint8_t getAttribute1(void) const {
        return attribute1;
    }

    bool getAttribute2(void) const {
        return attribute2;
    }
};