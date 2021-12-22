#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>

namespace delphioracle
{

    static constexpr eosio::name DELPHIORACLE_ACCOUNT = "delphioracle"_n;

    TABLE datapoints
    {
        uint64_t id;
        eosio::name owner;
        uint64_t value;
        uint64_t median;
        eosio::time_point timestamp;

        uint64_t primary_key() const { return id; }
        uint64_t by_timestamp() const { return timestamp.elapsed.to_seconds(); }
        uint64_t by_value() const { return value; }
    };

    typedef eosio::multi_index<"datapoints"_n, datapoints,
                               eosio::indexed_by<"value"_n, eosio::const_mem_fun<datapoints, uint64_t, &datapoints::by_value>>,
                               eosio::indexed_by<"timestamp"_n, eosio::const_mem_fun<datapoints, uint64_t, &datapoints::by_timestamp>>>
        datapointstable;

    datapointstable get_quote(eosio::name pair)
    {
        return datapointstable(DELPHIORACLE_ACCOUNT, pair.value);
    }

};
