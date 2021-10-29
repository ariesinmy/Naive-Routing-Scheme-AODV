# Naïve Routing Scheme: AODV (BFS)

無線隨意網路（英語：Wireless ad hoc network，mobile ad hoc network, 縮寫為WANET, MANET），又稱無線臨時網路[1][2]，是一種分散式的無線網路系統。ad hoc源自拉丁文，原意是臨時、專用、特設的。它被稱為ad hoc，是因為這種網路系統是臨時形成，由節點與節點間的動態連結所形成。它不需要依賴一個既存的網路架構，像是有線系統的路由器，或是無線系統的無線網路基地台。相反的，它每一個節點，都有能力轉送網路封包給其他節點（這稱為路由）。

當該網絡沒有了GPS定位功能後，每個節點就只會保存本地（local）信息(即鄰居信息)和目的地（destination）信息

![image](https://user-images.githubusercontent.com/58333941/139479502-54c805a1-969f-40fe-a606-08a67cc7a28a.png)

那我們要如何通過廣播（Broadcast）的方式，讓源節點可以快速地找到目的節點呢？
Ad hoc On Demand Distance Vector (AODV) protocol 是一個專門為 Ad hoc 移動網路所設計的通訊協定。
根據AODV協定，源節點只有在當向目的節點發送封包時，才會在網絡中發起路由查找過程，找到相應的路由。相反的，很多普通的網際網路路由協議都是先驗式的，也就是說它們查找路由是不依賴於路徑上的節點是否要發包，而是每個節點維護一張包含到達其它節點的路由信息的路由表。節點間通過周期性的交換路由信息來不斷更新自身的路由表，以便能夠及時的反映網絡拓撲結構和變化，以維護一致的、及時的、準確的路由信息。正如協議的名字所示，無線自組網按需平面距離矢量路由協議是一種平面距離矢量路由協議。

AODV 透過發出請求(Route Request，RREQ)與回覆(Route Reply，RREP)的機制來取得路由。首先，若來源點主機想傳輸到目的主機的路由資訊未建立，則 AODV 的來源主機會廣播 RREQ 訊
息至整個網路，收到此訊息的相鄰節點會更新收到來源點發出的資訊，並建立向後端來源點的路由表。

在 RREQ 中的訊息包含：來源主機的 IP 位址、來源端的序列號碼、廣播 ID、目的主機的 IP 位址、目的端的序列號碼，最後是經過的 hop 數。
在 RREP 中的訊息包含：來源主機的 IP 位址、目的主機的 IP 位址，目的端的序列號碼，經過的 hop 數以及連線的有效存活時間。

在該程式中，我們會以AODV的概念，以 BFS 的方式來建構類似系統：
1. 如果有多個節點具有相同的 hop 數，則向ID較小的節點發送RREQ
2. 在開始 routing 前，要先建構一個 routing table
3. 在 源節點 和 目的節點 之間，每個節點都會以“其距離源節點的 hop 數”來進行編號，該編號過程將會以 BFS 的方式完成，如下圖，每個節點都會有自己的routing table

![image](https://user-images.githubusercontent.com/58333941/139482377-9e500eab-1aa4-4da1-86d5-1fb447c49016.png)

4. 由每個節點的 routing table，我們便可以找到從 源節點 到 目的節點的路徑（但不一定是最短路徑）
5. input 格式：

![image](https://user-images.githubusercontent.com/58333941/139481949-8f37e8e9-c65e-4df9-b425-e2fb68ee1dda.png)

6. output 格式：
![image](https://user-images.githubusercontent.com/58333941/139481988-ade50e30-31f0-49d7-907c-e22f7a8e17e1.png)
