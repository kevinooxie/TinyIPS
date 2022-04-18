#pragma once 

#include <vector>
#include <stdexcept>

namespace TIPS
{
/**
 * Image of type T
 * Corrdinate conversion obey left->right, bottom->up
 *  -- i.e. (0,0) is the bottom-left pixel of image
 */
    template <class T>
    class Image 
    {
    public:
        // default image constructor
        explicit Image() { resize(); }

        // init image of given size without data
        Image(int width, int height) { resize(width, height); }

        // init image of given size with data
        Image(int width, int height, std::vector<T>& data)
            : width_(width), height_(height) 
        { 
            if (data.size() != (width*height))
                throw std::out_of_range("data size is not consistent with image dimensions");
            
            std::swap(data_, data);
        }

        // copy constructor
        Image(const Image<T>& other)
            : data_(other.data_), width_(other.width_), height_(other.height_) {}

        // move constructor
        Image(Image<T>&& other)
            : width_(other.width_), height_(other.height_)
        {
            std::swap(data_, other.data_);
            other.resize();    
        }

        // constructor with type conversion
        template<class T2>
        explicit Image(const Image<T2>& other)
        {
            resize(other.width_, other.height_);
            for (int i=0; i<size(); ++i)
                at1(i) = static_cast<T>(other.at1(i));
        }

        // assignment operator
        Image<T>& operator=(const Image<T>& other)
        {
            if (this == &other)
                return *this;
            //TODO: need to check if pixel type is matched 
            width_ = other.width_;
            height_ = other.height_;
            data_ = other.data_;
        }

        // pixel access operators
        const T& operator()(int x, int y) const
        {
            if (x<0 || x>=width_ || y<0 || y>=height_)
                throw std::out_of_range("Trying to access out of range value.");
            return data_[y * width_ + x];
        }
        T& operator()(int x, int y)
        {
            if (x<0 || x>=width_ || y<0 || y>=height_)
                throw std::out_of_range("Trying to access out of range value.");
            return data_[y * width_ + x];
        }

        // 1D pixel access
        const T& at1(int i) const 
        {
            if (i<0 || i>=size())
                throw std::out_of_range("Trying to access out of range value.");
            return data_[i];
        }
        T& at1(int i)
        {
            if (i<0 || i>=size())
                throw std::out_of_range("Trying to access out of range value.");
            return data_[i];
        }

        // return # pixels of the image
        int size() const { return width_*height_; }

        // fill the image with given value
        void fill(const T& val) { std::fill(data_.begin(), data_.end(), val); }

        // return image width
        int width() const { return width_; }

        // return image height
        int height() const { return height_; }

        // access the data of first element
        const T* data() const { return data_.data(); }
        T* data() { return data_.data(); }

        // check wheather two images are equal
        bool operator==(const Image<T>& im) const { return (width_==im.width_ && height_==im.height_ && data_==im.data_); }
        bool operator!=(const Image<T>& im) const { return !(*this == im); }

        // destructor
        virtual ~Image() {}

    private:
        std::vector<T> data_; // data stored in bottom-up raster order.
        int width_;
        int height_;

        void resize(int width=0, int height=0)
        {
            if (width<0 || height<0)
            {
                throw std::invalid_argument("Image dimensions must be non-negetive integers.");
            }

            width_ = width;
            height_ = height;
            data_.resize(width*height);
        }
    
    public:
        using iterator = typename decltype(data_)::iterator;
        using const_iterator = typename decltype(data_)::const_iterator;
        using reverse_iterator = typename decltype(data_)::reverse_iterator;
        using const_reverse_iterator = typename decltype(data_)::const_reverse_iterator;

        // return row-wise iterator
        iterator begin() { return data_.begin(); }
        const_iterator begin() const { return data.begin() }
        iterator end() { return data_.end(); }
        const_iterator end() { return data_.end(); }

    };

} // end of namespace TIPS


