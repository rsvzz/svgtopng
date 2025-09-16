class ChangedPG
{
private:
    /* data */
    int items;
    /// @brief refresh update
    double refresh;

    double next, update;
    bool status;
public:
    ChangedPG(int);
    ~ChangedPG();
    double get_next(); 
    double get_update();
    /// @brief valid next update
    /// @param  count actual
    void set_calc_update(int);
    /// @brief valid changed
    /// @return  True or False
    bool get_status();
};