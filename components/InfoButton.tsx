import { FontAwesome } from "@expo/vector-icons";
import React from "react";
import { Pressable, StyleSheet } from 'react-native'
import { useNavigation } from "@react-navigation/core";

export default function InfoButton(){

    const navigation = useNavigation();

    return(
        <Pressable 
            style={styles.infoHead}
            onPress = {() => {
                navigation.navigate("Information");
            }}
        >
            <FontAwesome name="info-circle" size={30} color='grey'/>
        </Pressable>
    )
}

const styles = StyleSheet.create({
    infoHead: {
        flexDirection: 'row-reverse',
        margin: 20,
    }
})