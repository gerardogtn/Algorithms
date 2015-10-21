#include <boost/graph/depth_first_search.hpp>

using namespace boost;
template<typename TimeMap>
class dfs_time_visitor: public default_dfs_visitor {

  typedef typename property_traits<TimeMap>::value_type T;

public:
  dfs_time_visitor(TimeMap dmap, TimeMap fmap, T & t) :  m_dtimemap(dmap),
      m_ftimemap(fmap), m_time(t) {

  }

  template <typename Vertex, typename graph_t>
  void discover_vertex(Vertex u, const graph_t & g) const
  {
    put(m_dtimemap, u, m_time++);
  }

  template < typename Vertex, typename graph_t >
  void finish_vertex(Vertex u, const graph_t & g) const
  {
    put(m_ftimemap, u, m_time++);
  }

  TimeMap m_dtimemap;
  TimeMap m_ftimemap;
  T & m_time;
};
