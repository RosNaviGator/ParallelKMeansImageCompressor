/**
 * @file point.hpp
 * @brief Point class representing a point in a feature space
 */

#ifndef POINT_HPP
#define POINT_HPP

#include <cmath>
#include <vector>

/**
 * @class Point
 * @brief Represents a point in a feature space
 */
class Point
{
public:
    int id{0};       ///< ID of the point
    unsigned char r{0}; ///< Red component
    unsigned char g{0}; ///< Green component
    unsigned char b{0}; ///< Blue component
    int clusterId{-1}; ///< ID of the cluster the point belongs to

    /**
     * @brief Constructor for Point
     * @param features_size Number of features
     */
    Point();

    /**
     * @brief Constructor for Point
     * @param id ID of the point
     * @param coordinates Coordinates of the point
     */
    Point(const int& id, const std::vector<int>& coordinates);

    /**
     * @brief Calculates the distance between this point and another point
     * @param p Other point
     * @return Distance between the points
     */
    [[nodiscard]] auto distance(const Point &p) const -> double;

    /**
     * @brief Gets a feature value at the specified index
     * @param index Index of the feature
     * @return Feature value
     */
    auto getFeature(int index) -> unsigned char&;

    /**
     * @brief Gets a feature value as an integer at the specified index
     * @param index Index of the feature
     * @return Feature value as an integer
     */
    [[nodiscard]] auto getFeature_int(int index) const -> int;

    /**
     * @brief Sets a feature value at the specified index
     * @param index Index of the feature
     * @param x Feature value
     */
    auto setFeature(int index, int x) -> void;
};

#endif // POINT_HPP