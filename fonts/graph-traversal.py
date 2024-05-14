from dataclasses import dataclass


@dataclass
class Node:
    index:int
    traversed:bool
    edges:list #list of indices
    x:int
    y:int



def createGraph(coords):
    nodes = [Node(i, False, list(), coord[0], coord[1]) for i, coord in enumerate(coords)]

    for n1 in nodes:
        edges = []

        for n2 in nodes[n1.index+1:]:
            adjacentX = (abs(n1.x - n2.x) == 1) and (n1.y == n2.y)
            adjacentY = (abs(n1.y - n2.y) == 1) and (n1.x == n2.x)
            adjacent = adjacentX or adjacentY
            if adjacent:
                n1.edges.append(n2.index)
                n2.edges.append(n1.index)


    # check for nodes with fewer than 2 edges, allow them to connect on diagonals
    for n1 in nodes:
        if len(n1.edges) >= 2: # already enough
            continue
        for n2 in nodes:
            if n1.index == n2.index: # no self connections
                continue
            if n2.index in n1.edges: # already connected
                continue
            diagonal = abs(n1.x - n2.x) == 1 and abs(n1.y - n2.y) == 1
            if diagonal:
                n1.edges.append(n2.index)
                n2.edges.append(n1.index)


    return nodes


def findStartingIndex(nodes:list[Node]):
    firstIndex = 0
    for node in nodes[1:]:
        first = nodes[firstIndex]

        if node.traversed: # node already traversed, cant be start
            continue

        if len(node.edges) > len(first.edges): # too many edges, looses
            continue

        if len(node.edges) < len(first.edges): # fewer edges, wins
            firstIndex = node.index
            continue

        #tie for number of edges

        if node.x > first.x: # same number of edges, but more right, looses
            continue

        if node.x < first.x: # same number of edges, but more left, wins
            firstIndex = node.index
            continue

        # tie for left right

        if node.y > first.y: # same number of edges, but more up, looses
            continue

        if node.y < first.y: # same number of edges, but more down, wins
            firstIndex = node.index
            continue

        #full tie, error out
        raise Exception("nodes appear identical")

    return firstIndex

def _traverseGraph(nodes:list[Node], node:Node, traversalIndices:list, backtrackIndices:list):

    if node.traversed:
        return

    # backtrack indices only get applied when traversing new nodes. not when exiting
    if len(backtrackIndices) > 0:
        traversalIndices.extend(backtrackIndices)
        backtrackIndices.clear()


    traversalIndices.append(node.index)
    node.traversed = True

    if len(node.edges) == 0:
        return

    #if len(node.edges) == 1:
    #    nextNode = nodes[node.edges[0]]
    #    if nextNode.traversed:
    #        return
    #    _traverseGraph(nodes, nextNode, traversalIndices, backtrackIndices)
    #    backtrackIndices.append(node.index)
    #    return


    for nodeIndex in node.edges:
        nextNode = nodes[nodeIndex]
        if nextNode.traversed:
            continue
        _traverseGraph(nodes, nextNode, traversalIndices, backtrackIndices)
        backtrackIndices.append(node.index) #


def allTraversed(nodes:list[Node]):
    for node in nodes:
        if not node.traversed:
            return False

    return True


def traverseGraph(nodes:list[Node]):
    segments = []
    while True:
        print("Segment:",len(segments))
        start = findStartingIndex(nodes)
        print(f"Start Index: {start}")
        traversalIndices = []
        exitPath = []
        _traverseGraph(nodes, nodes[start], traversalIndices, exitPath)
        print("Traversal:",traversalIndices)
        print("Exit:", exitPath)
        segments.append(traversalIndices)

        if allTraversed(nodes):
            break

        if len(segments) > 10:
            raise Exception("Too many segments")
    return segments



if __name__ == "__main__":
    # test = [[0,1],[0,2],[0,3],[1,0],[1,4],[2,0],[2,4],[3,1],[3,3]]
    test = [[0,0],[0,1],[0,2],[0,3],[0,4],[1,4],[2,4]] # L
    test = [[0,0],[0,1],[0,3],[0,4],[1,2],[2,0],[2,1],[2,3],[2,4]] # X
    test = [[0,4],[1,1],[1,3]] # ;
    graph = createGraph(test)
    #print(graph)
    segments = traverseGraph(graph)
    print("Number of segments found: ", len(segments))
    

