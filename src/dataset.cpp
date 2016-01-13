#include "dataset.h"

#include <iostream>

using namespace std;

namespace h5cpp {

Dataset::Dataset()
    : Object()
{
}

//Dataset::Dataset(Dataset &&other)
//    : Object(move(other))
//{
//}

Dataset::~Dataset()
{
    close();
}

Datatype::Type Dataset::datatype() const
{
    return datatype_impl().type();
}

bool Dataset::isScalar() const
{
    return dataspace().isScalar();
}

bool Dataset::isSimple() const
{
    return dataspace().isSimple();
}

vector<hsize_t> Dataset::extents() const
{
    return dataspace().extents();
}

Datatype Dataset::datatype_impl() const
{
    return Datatype(H5Dget_type(m_id));
}

Dataspace Dataset::dataspace() const
{
    return Dataspace(H5Dget_space(m_id));
}

int Dataset::dimensionCount() const
{
    return extents().size();
}

Dataset::Dataset(hid_t id, hid_t parentID, string name)
    : Object(id, parentID, name)
{
}

Dataset::Dataset(const Object &other)
    : Object()
{
    constructFromOther(other);
}

Dataset::Dataset(const Dataset &other)
    : Object()
{
    constructFromOther(other);
}

Dataset& Dataset::operator=(const Object &other)
{
    if(!other.isDataset()) {
        DVLOG(1) << "ERROR: Cannot assign to Dataset with " << other;
        return *this;
    }
    Object::operator=(other);
    return *this;
}

Dataset& Dataset::operator=(const Dataset &other)
{
    Object::operator=(other);
    return *this;
}

//Dataset& Dataset::operator=(Object &&other)
//{
//    Object &otherObject = other;
//    Object::operator=(move(otherObject));
//    return *this;
//}

//Dataset& Dataset::operator=(Dataset &&other)
//{
//    Object &otherObject = other;
//    Object::operator=(move(otherObject));
//    return *this;
//}

//void Dataset::constructFromOther(const Object &other)
//{
//    if(other.isValid() && other.isDataset()) {
//        close();
//        m_id = H5Dopen(other.id(), ".", H5P_DEFAULT);
//#ifdef H5CPP_VERBOSE
//        DVLOG(1) << "Opened dataset " << m_id << " from other " << other.id();
//#endif
//        m_name = other.name();
//        m_parentID = other.parentID();
//    } else if(other.id() == 0) {
//        close();
//        m_id = other.id();
//        m_name = other.name();
//        m_parentID = other.parentID();
//    } else {
//        DVLOG(1) << "ERROR: Cannot construct Dataset from " << other;
//    }
//}

//void Dataset::close()
//{
//    if(m_id > 0) {
//#ifdef H5CPP_VERBOSE
//    DVLOG(1) << "Closing dataset " << m_id;
//#endif
//        H5Dclose(m_id);
//        m_id = 0;
//    }
//}

}
